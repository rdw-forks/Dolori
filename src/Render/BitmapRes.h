#ifndef DOLORI_RENDER_BITMAPRES_H_
#define DOLORI_RENDER_BITMAPRES_H_

#include <il.h>
#include <stdint.h>
#include "Res.h"

class CBitmapRes : public CRes {
 public:
  CBitmapRes();
  ~CBitmapRes();

  uint32_t GetWidth();
  uint32_t GetHeight();
  const ILubyte *GetData();
  void Reset();
  unsigned int GetColor(int x, int y);
  bool Load(const char *);
  bool LoadFromBuffer(const char *, const uint8_t *, int);
  bool LoadBMPData(const uint8_t *, int);
  bool LoadTGAData(const uint8_t *, int);
  bool LoadJPGData(const uint8_t *, int);

 private:
  int m_isAlpha;
  uint32_t m_width;
  uint32_t m_height;
  ILubyte *m_data;
};

#endif  // DOLORI_RENDER_BITMAPRES_H_
