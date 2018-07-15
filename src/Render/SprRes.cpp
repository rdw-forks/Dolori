#include "Render/SprRes.h"

#include "Common/ErrorMsg.h"
#include "Common/Globals.h"
#include "Files/File.h"

CSprRes::CSprRes() : m_count() {}

CSprRes::~CSprRes() {}

CRes* CSprRes::Clone() {
  CRes* res;

  res = new CSprRes();
  if (res) {
    return res;
  }

  return nullptr;
}

void CSprRes::Reset() { m_count = 0; }

const uint32_t* CSprRes::GetPalette() { return m_pal; }

bool CSprRes::Load(const std::string& filename) {
  uint8_t palette[0x400];
  uint16_t rgba_count;
  SPR_HEADER header;
  CFile fp;

  if (!fp.Open(filename, false)) {
    std::string error = "Cannot find ";
    error += filename;
    ErrorMsg(error.c_str());
    return false;
  }

  fp.Read(&header, sizeof(header));
  if (header.magic != 'PS') {
    std::string error = "Illegal file format: ";
    error += filename;
    ErrorMsg(error.c_str());
    fp.Close();
    return false;
  }

  if (header.version > 0x201) {
    ErrorMsg("Unsupported version. Content may be corrupted");
    fp.Close();
    return false;
  }

  m_count = header.pal_img_count;
  /*printf("Version: %X\n", header.version);
  printf("No of clips: %d\n", m_count);*/
  if (header.version >= 0x200) fp.Read(&rgba_count, 2);

  if (m_count) {
    for (int i = 0; i < m_count; i++) {
      SPR_IMG* img = new SPR_IMG();

      fp.Read(img, 4);
      img->isHalfH = 0;
      img->isHalfW = 0;
      // img.tex = NULL;
      img->image_8bit = NULL;
      if (false /*g_isXHalfSpr || g_isYHalfSpr*/) {
        if (header.version < 0x201) {
        } else {
        }
      } else {
        if (header.version < 0x201) {
          // uint16_t uncompressed_size;
          // fp.Read(&uncompressed_size, 2);
          size_t size = img->width * img->height;
          img->image_8bit = new uint8_t[size];
          fp.Read(img->image_8bit, size);
        } else {
          uint16_t compressed_size;
          uint8_t* compressed_data;

          fp.Read(&compressed_size, sizeof(compressed_size));
          compressed_data = new uint8_t[compressed_size];
          fp.Read(compressed_data, compressed_size);
          img->image_8bit = DecodeRLE(compressed_data, img->width, img->height,
                                      &compressed_size);
          delete compressed_data;
        }
      }
      m_sprites[SPR_PAL].push_back(img);
    }
  }

  if (header.version >= 0x200 && rgba_count) {
  }

  // Palettes
  if (header.version > 0x101) {
    if (fp.Seek(-sizeof(palette), SEEK_END)) {
      fp.Read(palette, sizeof(palette));
      g_3dDevice->ConvertPalette(
          m_pal, reinterpret_cast<PALETTE_ENTRY*>(palette), 256);
    }
  }

  fp.Close();

  return true;
}

SPR_IMG* CSprRes::GetSprImg(SPR_TYPE clip_type, unsigned long spr_index) {
  if (clip_type > 2) {
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
