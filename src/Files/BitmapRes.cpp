#include "Files/BitmapRes.h"

#ifndef WIN32
#include <string.h>
#define _strcmpi strcasecmp
#endif

#include "Common/debug.h"
#include "Files/File.h"

CBitmapRes::CBitmapRes() : m_isAlpha(), m_width(), m_height(), m_data() {}

CBitmapRes::~CBitmapRes() { Reset(); }

uint32_t CBitmapRes::GetWidth() const { return m_width; }

uint32_t CBitmapRes::GetHeight() const { return m_height; }

const ILubyte* CBitmapRes::GetData() const { return m_data.data(); }

CRes* CBitmapRes::Clone() { return new CBitmapRes(); }

void CBitmapRes::Reset() {
  m_data.clear();
  m_width = 0;
  m_height = 0;
}

uint32_t CBitmapRes::GetColor(uint32_t x, uint32_t y) const {
  uint32_t result;

  if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
    result = 0x00FF0000;
  } else {
    result = m_data[x + y * m_width];
  }

  return result;
}

bool CBitmapRes::Load(const std::string& filename) {
  CFile file;

  if (!file.Open(filename, false)) {
    LOG(error, "Failed to find file: {}", filename);
    return false;
  }

  if (!LoadFromBuffer(filename, file.GetBuf(), file.GetLength())) {
    LOG(error, "Failed to parse file: {}", filename);
    return false;
  }

  return true;
}

bool CBitmapRes::LoadFromBuffer(const std::string& filename,
                                const uint8_t* buffer, size_t size) {
  const size_t dot_pos = filename.rfind('.');
  if (dot_pos == std::string::npos) {
    LOG(error, "Missing extension: {}", filename);
    return false;
  }

  if (filename.compare(dot_pos, 4, ".bmp") == 0) {
    return LoadBMPData(buffer, size);
  }

  if (filename.compare(dot_pos, 4, ".tga") == 0) {
    return LoadTGAData(buffer, size);
  }

  if (filename.compare(dot_pos, 4, ".jpg") == 0) {
    return LoadJPGData(buffer, size);
  }

  LOG(error, "Unsupported file format: {}", filename);
  return false;
}

bool CBitmapRes::LoadBMPData(const uint8_t* image, size_t size) {
  return LoadImageData(image, size, IL_BMP);
}

bool CBitmapRes::LoadTGAData(const uint8_t* image, size_t size) {
  return LoadImageData(image, size, IL_TGA);
}

bool CBitmapRes::LoadJPGData(const uint8_t* image, size_t size) {
  return LoadImageData(image, size, IL_JPG);
}

bool CBitmapRes::LoadImageData(const uint8_t* image, size_t size, ILenum type) {
  ILuint imgID = 0;

  Reset();
  ilGenImages(1, &imgID);
  ilBindImage(imgID);

  ILboolean success = ilLoadL(type, image, static_cast<ILuint>(size));
  if (success != IL_TRUE) {
    return false;
  }

  success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
  if (success != IL_TRUE) {
    return false;
  }

  const ILint Bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
  m_width = ilGetInteger(IL_IMAGE_WIDTH);
  m_height = ilGetInteger(IL_IMAGE_HEIGHT);
  m_data.resize(Bpp * m_width * m_height);
  memcpy(m_data.data(), ilGetData(), Bpp * m_width * m_height);

  // Replace purple pixels with transparent ones, as well as adjacent faded
  // pixels
  if (Bpp == 4) {
    const size_t data_size = m_width * m_height * 4;
    for (size_t i = 0; i < data_size - 3; i += 4) {
      if (m_data[i] > 250 && m_data[i + 1] < 5 && m_data[i + 2] > 250) {
        int totalr = 0;
        int totalg = 0;
        int totalb = 0;
        int total = 0;

        for (int delta_y = -1; delta_y <= 1; delta_y++) {
          for (int delta_x = -1; delta_x <= 1; delta_x++) {
            const int neighbour_i = i + (delta_x * 4) + (delta_y * m_width * 4);

            if (neighbour_i < 0 || neighbour_i >= data_size) {
              // Out of the image, continue
              continue;
            }

            if ((m_data[neighbour_i] > 250 && m_data[neighbour_i + 1] < 5 &&
                 m_data[neighbour_i + 2] > 250) ||
                m_data[neighbour_i + 3] == 0) {
              // Already taken care of
              continue;
            }

            totalr += m_data[neighbour_i];
            totalg += m_data[neighbour_i + 1];
            totalb += m_data[neighbour_i + 2];
            total++;
          }
        }

        if (total > 0) {
          m_data[i] = totalr / total;
          m_data[i + 1] = totalg / total;
          m_data[i + 2] = totalb / total;
        }

        m_data[i + 3] = 0;
      }
    }
  }

  ilDeleteImages(1, &imgID);

  return true;
}
