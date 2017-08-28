#include "UIWindowMgr.h"
#include "../Common/Globals.h"
#include "../UI/UINoticeConfirmWnd.h"

int UIX(int x) { return x + (g_Renderer->GetWidth() - 640) / 2; }

int UICY(int y) { return y * g_Renderer->GetHeight() / 480; }

CUIWindowMgr::CUIWindowMgr() {
  m_wallpaperSurface = NULL;
  m_children.clear();
}

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
      m_wallpaperSurface->Update(0, 0, bitmap->GetWidth(), bitmap->GetHeight(),
                                 bitmap->GetData(), 0);
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

void CUIWindowMgr::Render(CMode *mode) {
  for (auto it = m_children.begin(); it != m_children.end(); ++it) {
    CUIWindow *wnd = (CUIWindow *)*it;
    if (wnd->IsShow()) {
      wnd->DoDraw();
    }
  }
}

CUIFrameWnd *CUIWindowMgr::MakeWindow(WINDOWID windowId) {
  switch (windowId) {
    case WID_NOTICECONFIRMWND:
      CUINoticeConfirmWnd *wnd = new CUINoticeConfirmWnd();
      wnd->Create(280, 120);
      wnd->Move(UIX(185), UICY(300));
      AddWindow(wnd);
      break;
  };
  return NULL;
}

void CUIWindowMgr::AddWindow(CUIWindow *wnd) { m_children.push_back(wnd); }

void CUIWindowMgr::InvalidateUpdateNeededUI() {
  if (!m_isInvalidatedByForce) {
    m_isInvalidatedByForce = true;
    for (auto it = m_children.begin(); it != m_children.end(); ++it) {
      if ((*it)->IsUpdateNeeded()) (*it)->InvalidateChildren();
    }
  }
}