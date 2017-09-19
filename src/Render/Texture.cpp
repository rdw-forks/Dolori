#include "Texture.h"

CTexture::CTexture() {}

CTexture::CTexture(unsigned long w, unsigned long h, PIXEL_FORMAT pf) {
  m_lockCnt = 0;
  m_timeStamp = 0;
  m_texName[0] = 0;
  if (pf == PF_BUMP) {
    CreateBump(w, h);
  } else {
    Create(w, h, pf);
    while (w > m_w) w >>= 1;
    while (h > m_h) h >>= 1;

    m_updateHeight = h;
    m_updateWidth = w;
  }
}

CTexture::~CTexture() {}

// void CTexture::SetUVOffset(float u, float v) {
//  m_uOffset = u;
//  m_vOffset = v;
//}

void CTexture::Create(unsigned long width, unsigned long height,
                      PIXEL_FORMAT pf) {
  CSurface::Create(width, height);
  m_pf = pf;
}

bool CTexture::CreateBump(unsigned long w, unsigned long h) { return false; }