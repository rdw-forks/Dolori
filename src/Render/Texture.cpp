#include "Render/Texture.h"

CTexture::CTexture()
    : CSurface(),
      m_pf(),
      m_blackkey(),
      m_update_width(),
      m_update_height(),
      m_tex_name(),
      m_lock_count(),
      m_time_stamp() {}

CTexture::CTexture(unsigned long w, unsigned long h, PIXEL_FORMAT pf) {
  m_lock_count = 0;
  m_time_stamp = 0;
  m_tex_name[0] = 0;
  if (pf == PF_BUMP) {
    CreateBump(w, h);
    return;
  }

  Create(w, h, pf);
  while (w > m_w) {
    w >>= 1;
  }

  while (h > m_h) {
    h >>= 1;
  }
  m_update_height = h;
  m_update_width = w;
}

CTexture::CTexture(unsigned long w, unsigned long h, PIXEL_FORMAT pf,
                   SDL_Surface *surface) {
  m_sdl_surface = nullptr;
  m_lock_count = 0;
  m_time_stamp = 0;
  m_pf = pf;
  m_w = w;
  m_h = h;
  if (pf == PF_BUMP) {
    CreateBump(w, h);
  } else {
    m_sdl_surface = surface;
  }
}

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

unsigned long CTexture::GetUpdateWidth() { return m_update_width; }

unsigned long CTexture::GetUpdateHeight() { return m_update_height; }

void CTexture::UpdateTimestamp() { m_time_stamp = GetTick(); }
