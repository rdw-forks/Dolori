#include "UIWindowMgr.h"
#include "../Common/Globals.h"
#include "../UI/UINoticeConfirmWnd.h"
#include "../UI/UISelectServerWnd.h"

// Helper functions
int UIX(int x) { return x + (g_Renderer->GetWidth() - 640) / 2; }
int UICY(int y) { return y * g_Renderer->GetHeight() / 480; }

CUIWindowMgr::CUIWindowMgr() {
  m_wallpaperSurface = NULL;
  m_children.clear();
  m_captureWindow = NULL;
  m_editWindow = NULL;
  m_modalWindow = NULL;
  m_last_hit_window = NULL;
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
      wnd->DoDraw(false);
      wnd->DrawSurface();
    }
  }
}

CUIFrameWnd *CUIWindowMgr::MakeWindow(WINDOWID windowId) {
  CUIFrameWnd *result = NULL;

  switch (windowId) {
    case WID_NOTICECONFIRMWND: {
      CUINoticeConfirmWnd *wnd = new CUINoticeConfirmWnd();
      wnd->Create(280, 120);
      wnd->Move(UIX(185), UICY(300));
      AddWindow(wnd);
      result = wnd;
    } break;
    case WID_LOGINWND:
      m_loginWnd = new CUILoginWnd();
      m_loginWnd->Create(280, 120);
      m_loginWnd->Move(UIX(185), UICY(300));
      AddWindow(m_loginWnd);
      result = m_loginWnd;
      break;
    case WID_SELECTSERVERWND: {
      CUISelectServerWnd *wnd = new CUISelectServerWnd();
      // wnd->Create(280, 200);
      wnd->Create(280, 120);
      wnd->Move(UIX(185), UICY(300) - 80);
      AddWindow(wnd);
      result = wnd;
    } break;
    case WID_SELECTCHARWND: {
      m_selectCharWnd = new CUISelectCharWnd();
      m_selectCharWnd->Create(576, 342);
      m_selectCharWnd->Move(UIX(33), UICY(1) + 65);
      AddWindow(m_selectCharWnd);
      result = m_selectCharWnd;
    } break;
  };

  return result;
}

void CUIWindowMgr::PostQuit(CUIWindow *wnd) {
  // if (wnd == m_selectCharWnd)
  //  m_selectCharWnd = NULL;
  // if (wnd == m_selCharForUServerWnd)
  //  m_selCharForUServerWnd = NULL;
  // if (wnd == m_changeNameWnd)
  //  m_changeNameWnd = NULL;
  m_quit_window.push_back(wnd);
}

void CUIWindowMgr::AddWindow(CUIWindow *window) {
  m_children.push_back(window);
}

void CUIWindowMgr::RemoveWindow(CUIWindow *window) {
  m_children.remove(window);
}

void CUIWindowMgr::RemoveAllWindows() { m_children.clear(); }

void CUIWindowMgr::InvalidateUpdateNeededUI() {
  if (!m_isInvalidatedByForce) {
    m_isInvalidatedByForce = true;
    for (auto it = m_children.begin(); it != m_children.end(); ++it) {
      if ((*it)->IsUpdateNeeded()) (*it)->InvalidateChildren();
    }
  }
}

CUIWindow *CUIWindowMgr::GetCapture() { return m_captureWindow; }

void CUIWindowMgr::SetCapture(CUIWindow *window) { m_captureWindow = window; }

void CUIWindowMgr::ReleaseCapture() { m_captureWindow = NULL; }

void CUIWindowMgr::SetFocusEdit(CUIWindow *window) {
  if (m_editWindow) m_editWindow->OnFinishEdit();
  if (true /*window != m_chatWnd->m_commonChat*/) {
    m_editWindow = window;
    if (window) window->OnBeginEdit();
  }
}

CUIWindow *CUIWindowMgr::GetFocusEdit() { return m_editWindow; }

int CUIWindowMgr::ProcessInput() {
  int x = g_Mouse->GetXPos();
  int y = g_Mouse->GetYPos();

  if (!m_modalWindow) {
    for (auto it = m_quit_window.begin(); it != m_quit_window.end(); ++it) {
      if (m_captureWindow &&
          (m_captureWindow == *it || m_captureWindow->IsChildOf(*it))) {
        m_captureWindow = NULL;
      }
      if (m_editWindow &&
          (m_editWindow == *it || m_editWindow->IsChildOf(*it))) {
        m_editWindow = NULL;
      }
      if (m_modalWindow &&
          (m_modalWindow == *it || m_modalWindow->IsChildOf(*it))) {
        m_modalWindow = NULL;
      }
      if (m_last_hit_window &&
          (m_last_hit_window == *it || m_last_hit_window->IsChildOf(*it))) {
        m_last_hit_window = NULL;
      }
      RemoveWindow(*it);
    }
    m_quit_window.clear();
  }

  if (!m_captureWindow) {
    CUIWindow *hit_window = NULL;

    if (m_children.empty())
      hit_window = NULL;
    else {
      for (auto it = m_children.rbegin(); it != m_children.rend(); ++it) {
        hit_window = (*it)->HitTest(x, y);
        if (hit_window && hit_window->IsShow()) break;
      }
    }

    if (m_modalWindow) {
      if (!hit_window) {
      }
    }

    if (hit_window) {
      int x_global, y_global;
      int x_local, y_local;

      hit_window->GetGlobalCoor(&x_global, &y_global);
      x_local = x - x_global;
      y_local = y - y_global;

      if (g_Mouse->GetLBtn() == BTN_DOWN)
        hit_window->OnLBtnDown(x_local, y_local);
      else if (g_Mouse->GetLBtn() == BTN_DBLCLK)
        hit_window->OnLBtnDblClk(x - x_global, y - y_global);
      if (g_Mouse->GetRBtn() == BTN_DOWN)
        hit_window->OnRBtnDown(x_local, y_local);
      else if (g_Mouse->GetRBtn() == BTN_DBLCLK)
        hit_window->OnRBtnDblClk(x - x_global, y - y_global);
      if (g_Mouse->GetWBtn() == BTN_DOWN)
        hit_window->OnWBtnDown(x_local, y_local);

      hit_window->OnMouseShape(x_local, y_local);
      if (m_last_mouse_x != x || m_last_mouse_y != y)
        hit_window->OnMouseMove(x_local, y_local);
      else
        hit_window->OnMouseHover(x_local, y_local);

      if (g_Mouse->GetWBtn() == BTN_UP) hit_window->OnWBtnUp(x_local, y_local);
      if (g_Mouse->GetRBtn() == BTN_UP) hit_window->OnRBtnUp(x_local, y_local);
      if (g_Mouse->GetLBtn() == BTN_UP) hit_window->OnLBtnUp(x_local, y_local);

      if (m_last_hit_window && hit_window != m_last_hit_window) {
        m_last_hit_window->GetGlobalCoor(&x_global, &y_global);
        x_local = x - x_global;
        y_local = y - y_global;
        m_last_hit_window->OnMouseMove(x_local, y_local);
        m_last_hit_window->OnMouseShape(x_local, y_local);
      }
      m_last_hit_window = hit_window;
    }
  } else {
    int x_global, y_global;
    int x_local, y_local;

    m_captureWindow->GetGlobalCoor(&x_global, &y_global);
    x_local = x - x_global;
    y_local = y - y_global;

    if (g_Mouse->GetLBtn() == BTN_DOWN) {
    } else if (g_Mouse->GetLBtn() == BTN_DBLCLK) {
      m_captureWindow->OnLBtnDown(x_local, y_local);
      m_captureWindow->OnLBtnDblClk(x_local, y_local);
    }

    m_captureWindow->OnMouseShape(x_local, y_local);
    if (m_last_mouse_x != x || m_last_mouse_y != y)
      m_captureWindow->OnMouseMove(x_local, y_local);
    else
      m_captureWindow->OnMouseHover(x_local, y_local);
    // if (g_Mouse.m_wheel)
    //  m_captureWindow->OnWheel(g_mouse.m_wheel);
    if (g_Mouse->GetLBtn() == BTN_UP)
      m_captureWindow->OnLBtnUp(x_local, y_local);
  }

  if (m_editWindow) m_editWindow->Invalidate();
  // g_mouseMoved = false;
  // if (x != m_lastMouseX || y != m_lastMouseY)
  //  g_mouseMoved = true;
  m_last_mouse_x = x;
  m_last_mouse_y = y;
  // if (!m_modalWindow)
  //  return rValue;

  return 1;
}

int CUIWindowMgr::ErrorMsg(const char *msg, int type, int isDefYes,
                           int changeMsg, unsigned int autoReturnTime) {
  printf("%s\n", msg);

  return 0;
}