#include "TexMgr.h"

#include "Common/Globals.h"

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
  if (!filename) {
    return nullptr;
  }

  auto it = m_tex_table.find(filename);
  if (it != std::end(m_tex_table)) {
    it->second->UpdateTimestamp();
    return it->second;
  }

  CBitmapRes* bitmap =
      reinterpret_cast<CBitmapRes*>(g_ResMgr->Get(filename, false));
  if (!bitmap) {
    // Create shit
    return nullptr;
  }

  auto tex = new CTexture(bitmap->GetWidth(), bitmap->GetHeight(), PF_A8R8G8B8);

  tex->Update(0, 0, bitmap->GetWidth(), bitmap->GetHeight(), bitmap->GetData(),
              0);

  m_tex_table[filename] = tex;

  return tex;
}
