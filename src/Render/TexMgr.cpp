#include "TexMgr.h"

CTexMgr::CTexMgr() {}

CTexMgr::~CTexMgr() {}

CTexture* CTexMgr::CreateTexture(unsigned long w, unsigned long h,
                                 PIXEL_FORMAT pf) {
  return new CTexture(w, h, pf);
}
