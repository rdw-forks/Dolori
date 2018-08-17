#include "Files/BitmapRes.h"

#ifndef WIN32
#include <string.h>
#define _strcmpi strcasecmp
#endif

#include "Common/ErrorMsg.h"
#include "Files/File.h"

CBitmapRes::CBitmapRes() : m_isAlpha(), m_width(), m_height(), m_data() {}

CBitmapRes::~CBitmapRes() {
  if (m_data) {
    delete[] m_data;
  }
}

uint32_t CBitmapRes::GetWidth() { return m_width; }

uint32_t CBitmapRes::GetHeight() { return m_height; }

const ILubyte* CBitmapRes::GetData() { return m_data; }

CRes* CBitmapRes::Clone() {
  CRes* res;

  res = new CBitmapRes();
  if (res) {
    return res;
  }

  return nullptr;
}

void CBitmapRes::Reset() {
  if (m_data) {
    delete[] m_data;
    m_data = nullptr;
  }

  m_width = 0;
  m_height = 0;
}

unsigned int CBitmapRes::GetColor(int x, int y) {
  unsigned int result;

  if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
    result = 0x00FF0000;
  } else {
    result = m_data[x + y * m_width];
  }

  return result;
}

bool CBitmapRes::Load(const std::string& fName) {
  CFile* fp;

  fp = new CFile();
  if (fp->Open(fName, 0)) {
    if (LoadFromBuffer(fName, fp->GetBuf(), fp->GetLength())) {
      delete fp;
      return true;
    }
  }
  delete fp;

  return false;
}

bool CBitmapRes::LoadFromBuffer(const std::string& fName, const uint8_t* buffer,
                                size_t size) {
  const char* str_extension;

  str_extension = strrchr(fName.c_str(), '.');
  if (str_extension) {
    if (!_strcmpi(str_extension, ".bmp")) {
      return LoadBMPData(buffer, size);
    }

    if (!_strcmpi(str_extension, ".tga")) {
      return LoadTGAData(buffer, size);
    }

    if (!_strcmpi(str_extension, ".jpg")) {
      return LoadJPGData(buffer, size);
    }

    ErrorMsg("Unsupported file format");
  }

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

  ILboolean success = ilLoadL(type, image, size);
  if (success != IL_TRUE) {
    return false;
  }

  success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
  if (success != IL_TRUE) {
    return false;
  }

  m_width = ilGetInteger(IL_IMAGE_WIDTH);
  m_height = ilGetInteger(IL_IMAGE_HEIGHT);
  ILint Bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
  m_data = new ILubyte[Bpp * m_width * m_height];
  memcpy(m_data, ilGetData(), Bpp * m_width * m_height);
  ilDeleteImages(1, &imgID);

  // If the image was a BMP, replace purple pixels with transparent ones
  if (type == IL_BMP && Bpp == 4) {
    size_t data_size = m_width * m_height * 4;
    for (int i = 0; i < data_size - 3; i += 4) {
      if (m_data[i] == 0xFF && m_data[i + 1] == 0x00 && m_data[i + 2] == 0xFF) {
        m_data[i + 3] = 0x00;
      }
    }
  }

  return true;
}
