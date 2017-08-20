#include "BitmapRes.h"
#include <string.h>
#include <iostream>
#include "../Files/File.h"

CBitmapRes::CBitmapRes() {
  m_isAlpha = 0;
  m_data = NULL;
  m_width = 0;
  m_height = 0;
}

CBitmapRes::~CBitmapRes() {
  if (m_data) free(m_data);
}

uint32_t CBitmapRes::GetWidth() { return m_width; }

uint32_t CBitmapRes::GetHeight() { return m_height; }

const ILubyte* CBitmapRes::GetData() { return m_data; }

void CBitmapRes::Reset() {
  if (m_data) free(m_data);
  m_width = 0;
  m_height = 0;
  m_data = 0;
}

unsigned int CBitmapRes::GetColor(int x, int y) {
  unsigned int result;

  if (x < 0 || x >= m_width || y < 0 || y >= m_height)
    result = 0x00FF0000;
  else
    result = m_data[x + y * m_width];

  return result;
}

bool CBitmapRes::Load(const char* fName) {
  CFile* fp;

  fp = new CFile();
  if (fName && fp->Open(fName, 0)) {
    if (LoadFromBuffer(fName, fp->GetBuf(), fp->GetLength())) {
      delete fp;
      return true;
    }
  }
  delete fp;

  return false;
}

bool CBitmapRes::LoadFromBuffer(const char* fName, const uint8_t* buffer,
                                int size) {
  const char* str_extension;

  str_extension = strrchr(fName, '.');
  if (str_extension) {
    if (!_strcmpi(str_extension, ".bmp")) return LoadBMPData(buffer, size);
    if (!_strcmpi(str_extension, ".tga")) return LoadTGAData(buffer, size);
    if (!_strcmpi(str_extension, ".jpg")) return LoadJPGData(buffer, size);
    // ErrorMsg(aUnsupportFilef);
  }

  return false;
}

bool CBitmapRes::LoadBMPData(const uint8_t* bitmap, int size) {
  ILuint imgID = 0;

  Reset();
  ilGenImages(1, &imgID);
  ilBindImage(imgID);

  ILboolean success = ilLoadL(IL_BMP, bitmap, size);
  if (success != IL_TRUE) return false;

  success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
  if (success != IL_TRUE) return false;

  m_width = ilGetInteger(IL_IMAGE_WIDTH);
  m_height = ilGetInteger(IL_IMAGE_HEIGHT);
  ILint Bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
  m_data = (ILubyte*)malloc(Bpp * m_width * m_height);
  memcpy(m_data, ilGetData(), Bpp * m_width * m_height);
  std::cout << "Width : " << m_width << std::endl;
  std::cout << "height : " << m_height << std::endl;
  std::cout << "Bytes per pixel : " << Bpp << std::endl;
  ilDeleteImages(1, &imgID);

  return true;
}

bool CBitmapRes::LoadTGAData(const uint8_t* bitmap, int size) { return false; }

bool CBitmapRes::LoadJPGData(const uint8_t* bitmap, int size) { return false; }