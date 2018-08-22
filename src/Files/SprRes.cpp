#include "Files/SprRes.h"

#include "Common/Globals.h"
#include "Common/debug.h"
#include "Files/File.h"

#define SPR_RES_HEADER "SP"

#pragma pack(push)
#pragma pack(1)

typedef struct _SprHeader {
  uint16_t magic;
  uint8_t version_major;
  uint8_t version_minor;
  uint16_t pal_img_count;
} SprHeader;

#pragma pack(pop)

CSprRes::CSprRes() : m_sprites(), m_count() {}

CSprRes::~CSprRes() { Reset(); }

CRes* CSprRes::Clone() { return new CSprRes(); }

void CSprRes::Reset() {
  for (size_t i = 0; i < SPR_TYPE_COUNT; i++) {
    for (auto img : m_sprites[i]) {
      if (img->image_8bit != nullptr) {
        delete[] img->image_8bit;
      }
      delete img;
    }

    m_sprites[i].clear();
  }

  m_count = 0;
}

const uint32_t* CSprRes::GetPalette() { return m_palette; }

bool CSprRes::Load(const std::string& filename) {
  uint8_t palette[0x400];
  uint16_t rgba_count;
  SprHeader header;
  CFile fp;

  if (!fp.Open(filename, false)) {
    LOG(error, "Failed to find file: {}", filename);
    return false;
  }

  fp.Read(&header, sizeof(header));
  if (memcmp(&header.magic, SPR_RES_HEADER, sizeof(header.magic)) != 0) {
    LOG(error, "Failed to parse file: {}", filename);
    return false;
  }

  const uint16_t version = (header.version_major << 8) | (header.version_minor);
  LOG(debug, "SPR file version: {:x}", version);

  if (version > 0x201) {
    LOG(error, "Unsupported version.");
    return false;
  }

  m_count = header.pal_img_count;
  if (version >= 0x101) {
    fp.Read(&rgba_count, sizeof(rgba_count));
  }

  for (uint16_t i = 0; i < m_count; i++) {
    SPR_IMG* img = new SPR_IMG();

    fp.Read(&img->width, sizeof(img->width));
    fp.Read(&img->height, sizeof(img->height));
    img->isHalfH = 0;
    img->isHalfW = 0;
    img->image_8bit = nullptr;
    if (version >= 0x200) {
      // Read pal images
      size_t size = img->width * img->height;
      img->image_8bit = new uint8_t[size];
      fp.Read(img->image_8bit, size);
    } else {
      // Read encoded pal images
      uint16_t compressed_size;
      uint8_t* compressed_data;

      fp.Read(&compressed_size, sizeof(compressed_size));
      compressed_data = new uint8_t[compressed_size];
      fp.Read(compressed_data, compressed_size);
      img->image_8bit =
          DecodeRLE(compressed_data, img->width, img->height, &compressed_size);
      delete compressed_data;
    }

    m_sprites[SPR_TYPE_PAL].push_back(img);
  }

  if (version >= 0x200 && rgba_count) {
    // TODO: Read RGBA images
  }

  // Palettes
  if (version > 0x100) {
    if (fp.Seek(-sizeof(palette), SEEK_END)) {
      fp.Read(palette, sizeof(palette));
      g_3dDevice->ConvertPalette(m_palette,
                                 reinterpret_cast<PALETTE_ENTRY*>(palette),
                                 sizeof(m_palette) / sizeof(m_palette[0]));
    }
  }

  fp.Close();

  return true;
}

SPR_IMG* CSprRes::GetSprImg(SPR_TYPE clip_type, unsigned long spr_index) {
  if (clip_type > SPR_TYPE_COUNT) {
    return nullptr;
  }

  if (spr_index > m_sprites[clip_type].size()) {
    return nullptr;
  }

  return m_sprites[clip_type][spr_index];
}

uint8_t* CSprRes::DecodeRLE(uint8_t* image, int w, int h,
                            unsigned short* size) {
  if (*size < 1) {
    return image;
  }

  uint8_t* output = new uint8_t[w * h];
  size_t output_index = 0;
  size_t input_index = 0;
  uint8_t count;

  while (input_index < *size) {
    uint8_t c = image[input_index++];
    output[output_index++] = c;

    if (!c) {
      count = image[input_index++];
      if (!count) {
        output[output_index++] = count;
      } else {
        for (int i = 1; i < count; i++) {
          output[output_index++] = c;
        }
      }
    }
  }

  *size = output_index - 1;

  return output;
}