#include "UIWindowMgr.h"
#include "../Common/Globals.h"

CUIWindowMgr::CUIWindowMgr() { m_wallpaperSurface = NULL; }

CUIWindowMgr::~CUIWindowMgr() {}

void CUIWindowMgr::SetSize(int cx, int cy) {
  m_w = cx;
  m_h = cy;
  m_chatWndX = 0;
  m_chatWndY = cy - m_chatWndHeight;
}

void CUIWindowMgr::SetWallpaper(CBitmapRes *bitmap) {
  if (bitmap) {
    if (!m_wallpaperSurface) {
      m_wallpaperSurface =
          g_3dDevice->CreateWallPaper(bitmap->GetWidth(), bitmap->GetHeight());
    }
    if (m_wallpaperSurface)
      m_wallpaperSurface->Update(bitmap->GetWidth(), bitmap->GetHeight(),
                                 bitmap->GetData());
  } else {
    if (m_wallpaperSurface) {
      delete m_wallpaperSurface;
      m_wallpaperSurface = NULL;
    }
  }
}

void CUIWindowMgr::RenderWallPaper() {
  m_isInvalidatedByForce = false;
  if (m_wallpaperSurface) {
    m_wallpaperSurface->DrawSurfaceStretch((g_3dDevice->GetWidth() - m_w) / 2,
                                           (g_3dDevice->GetHeight() - m_h) / 2,
                                           m_w, m_h);
  }
}