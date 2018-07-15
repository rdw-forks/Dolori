#ifndef DOLORI_RENDER_BITMAPRES_H_
#define DOLORI_RENDER_BITMAPRES_H_

#include <stdint.h>

#include <string>

#include <il.h>

#include "Render/Res.h"

class CBitmapRes : public CRes {
 public:
  CBitmapRes();
  ~CBitmapRes();

  uint32_t GetWidth();
  uint32_t GetHeight();
  const ILubyte *GetData();
  CRes *Clone();
  void Reset();
  unsigned int GetColor(int x, int y);
  bool Load(const std::string &);
  bool LoadFromBuffer(const std::string &, const uint8_t *, size_t);
  bool LoadBMPData(const uint8_t *, size_t);
  bool LoadTGAData(const uint8_t *, size_t);
  bool LoadJPGData(const uint8_t *, size_t);

 private:
  bool LoadImageData(const uint8_t *, size_t, ILenum);

 private:
  int m_isAlpha;
  uint32_t m_width;
  uint32_t m_height;
  ILubyte *m_data;
};

#endif  // DOLORI_RENDER_BITMAPRES_H_
