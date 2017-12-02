#include "TexMgr.h"

CTexMgr::CTexMgr() {}

CTexMgr::~CTexMgr() {}

CTexture* CTexMgr::CreateTexture(unsigned long w, unsigned long h,
                                 PIXEL_FORMAT pf) {
  return new CTexture(w, h, pf);
}

CTexture* CTexMgr::CreateTexture(unsigned long w, unsigned long h,
                                 PIXEL_FORMAT pf, SDL_Surface* surface) {
  if (surface) {
    return new CTexture(w, h, pf, surface);
  }
  return new CTexture(w, h, pf);
}

CTexture* CTexMgr::GetTexture(const char* filename, bool blackkey) {
  return nullptr;
}
