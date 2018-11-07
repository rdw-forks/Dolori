#include "Files/SprRes.h"

#include "Common/Globals.h"
#include "Common/debug.h"
#include "Files/File.h"

#define SPR_RES_HEADER "SP"

#pragma pack(push)
#pragma pack(1)

typedef struct _SprHeader {
  uint16_t magic;
  uint16_t version;
  uint16_t pal_img_count;
} SprHeader;

#pragma pack(pop)

CSprRes::CSprRes() : m_palette(), m_sprites(), m_count() {}

CSprRes::~CSprRes() { Reset(); }

CRes* CSprRes::Clone() { return new CSprRes(); }

void CSprRes::Reset() {
  for (auto& sprite : m_sprites) {
    for (auto& img : sprite) {
      img->image_8bit.clear();
    }

    sprite.clear();
  }

  m_count = 0;
}

const uint32_t* CSprRes::GetPalette() const {
  return static_cast<const uint32_t*>(m_palette);
}

bool CSprRes::Load(const std::string& filename) {
  uint8_t palette[0x400];
  uint16_t rgba_count;
  SprHeader header;
  CFile fp;

  if (!fp.Open(filename, 0)) {
    LOG(error, "Failed to find file: {}", filename);
    return false;
  }

  fp.Read(&header, sizeof(header));
  if (memcmp(&header.magic, SPR_RES_HEADER, sizeof(header.magic)) != 0) {
    LOG(error, "Failed to parse file: {}", filename);
    return false;
  }

  const uint16_t version = header.version;
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
    auto img = std::make_unique<SprImg>();

    fp.Read(&img->width, sizeof(img->width));
    fp.Read(&img->height, sizeof(img->height));
    img->isHalfH = 0;
    img->isHalfW = 0;
    if (version < 0x201) {
      // Read pal images
      const size_t size =
          static_cast<size_t>(img->width) * static_cast<size_t>(img->height);
      img->image_8bit.resize(size);
      fp.Read(img->image_8bit.data(), img->image_8bit.size());
    } else {
      // Read encoded pal images
      uint16_t compressed_size;
      std::vector<uint8_t> compressed_data;

      fp.Read(&compressed_size, sizeof(compressed_size));
      compressed_data.resize(compressed_size);
      fp.Read(compressed_data.data(), compressed_data.size());
      DecodeRLE(compressed_data, img->width, img->height, img->image_8bit);
    }

    m_sprites[SPR_TYPE_PAL].push_back(std::move(img));
  }

  if (version >= 0x200 && rgba_count != 0) {
    // TODO(LinkZ): Read RGBA images
  }

  // Palettes
  if (version > 0x100) {
    if (fp.Seek(0 - sizeof(palette), SEEK_END)) {
      fp.Read(palette, sizeof(palette));
      g_3dDevice->ConvertPalette(m_palette,
                                 reinterpret_cast<PALETTE_ENTRY*>(palette),
                                 sizeof(m_palette) / sizeof(m_palette[0]));
    }
  }

  fp.Close();

  return true;
}

SprImg* CSprRes::GetSprImg(SPR_TYPE clip_type, size_t spr_index) const {
  if (clip_type >= SPR_TYPE_COUNT) {
    return nullptr;
  }

  if (spr_index > m_sprites[clip_type].size()) {
    return nullptr;
  }

  // Return a non-owning pointer to the sprite img
  return m_sprites[clip_type][spr_index].get();
}

void CSprRes::DecodeRLE(const std::vector<uint8_t>& image, int w, int h,
                        std::vector<uint8_t>& output) {
  size_t output_index = 0;
  size_t input_index = 0;
  uint8_t count;

  output.resize(static_cast<size_t>(w) * static_cast<size_t>(h));
  while (input_index < image.size()) {
    const uint8_t c = image[input_index++];
    output[output_index++] = c;

    if (c == 0) {
      count = image[input_index++];
      if (count == 0) {
        output[output_index++] = count;
      } else {
        for (int i = 1; i < count; i++) {
          output[output_index++] = c;
        }
      }
    }
  }
}
