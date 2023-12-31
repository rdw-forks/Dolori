#include "Core/UIWindowMgr.h"

#include "Common/Globals.h"
#include "Common/debug.h"
#include "UI/UIMakeCharWnd.h"
#include "UI/UINoticeConfirmWnd.h"
#include "UI/UISelectServerWnd.h"

// Helper functions
int UIX(int x) { return x + (g_Renderer->GetWidth() - 640) / 2; }
int UICY(int y) { return y * g_Renderer->GetHeight() / 480; }

CUIWindowMgr::CUIWindowMgr()
    : m_chatWndX(0),
      m_chatWndY(0),
      m_chatWndHeight(98),
      m_chatWndShow(1),
      m_chatWndStatus(7),
      m_battle_mode(true),
      m_conversionMode(),
      m_captureWindow(),
      m_editWindow(),
      m_modalWindow(),
      m_last_hit_window(),
      m_chatWnd(),
      m_loginWnd(),
      m_selectCharWnd(),
      m_wallpaperSurface() {
  m_children.clear();
}

void CUIWindowMgr::SetSize(int cx, int cy) {
  m_w = cx;
  m_h = cy;
  m_chatWndX = 0;
  m_chatWndY = cy - m_chatWndHeight;
}

void CUIWindowMgr::SetWallpaper(CBitmapRes *bitmap) {
  if (bitmap == nullptr) {
    // Destroy previously set wallpaper
    m_wallpaperSurface = nullptr;
    return;
  }

  if (m_wallpaperSurface == nullptr) {
    m_wallpaperSurface =
        g_3dDevice->CreateWallPaper(bitmap->GetWidth(), bitmap->GetHeight());
  }

  if (m_wallpaperSurface != nullptr) {
    m_wallpaperSurface->Update(0, 0, bitmap->GetWidth(), bitmap->GetHeight(),
                               bitmap->GetData(), 0);
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
  for (auto child : m_children) {
    if (child->IsShow()) {
      child->DoDraw(false);
      child->DrawSurface();
    }
  }
}

void CUIWindowMgr::OnProcess() {
  std::for_each(std::begin(m_children), std::end(m_children),
                [](CUIWindow *window) { window->OnProcess(); });
}

CUIFrameWnd *CUIWindowMgr::MakeWindow(WindowId windowId) {
  CUIFrameWnd *result = nullptr;

  switch (windowId) {
    case WID_BASICINFOWND:
      break;
    case WID_CHATWND:
      if (m_chatWnd == nullptr) {
        m_chatWnd = new CUINewChatWnd(this);
        if (m_chatWnd == nullptr) {
          break;
        }

        m_chatWnd->Create(600, m_chatWndHeight);
        AddWindow(m_chatWnd);
      }

      m_chatWnd->SendMsg(nullptr, 34);
      break;
    case WID_NOTICECONFIRMWND: {
      auto wnd = new CUINoticeConfirmWnd(this);
      wnd->Create(280, 120);
      wnd->Move(UIX(185), UICY(300));
      AddWindow(wnd);
      result = wnd;
    } break;
    case WID_LOGINWND:
      m_loginWnd = new CUILoginWnd(this);
      m_loginWnd->Create(280, 120);
      m_loginWnd->Move(UIX(185), UICY(300));
      AddWindow(m_loginWnd);
      result = m_loginWnd;
      break;
    case WID_SELECTSERVERWND: {
      auto wnd = new CUISelectServerWnd(this);
      wnd->Create(280, 120);
      wnd->Move(UIX(185), UICY(300) - 80);
      AddWindow(wnd);
      result = wnd;
    } break;
    case WID_SELECTCHARWND: {
      m_selectCharWnd = new CUISelectCharWnd(this);
      m_selectCharWnd->Create(576, 342);
      m_selectCharWnd->Move(UIX(33), UICY(1) + 65);
      AddWindow(m_selectCharWnd);
      result = m_selectCharWnd;
    } break;
    case WID_MAKECHARWND: {
      auto makeCharWnd = new CUIMakeCharWnd(this);
      makeCharWnd->Create(576, 342);
      makeCharWnd->Move(UIX(33), UICY(1) + 65);
      AddWindow(makeCharWnd);
      result = makeCharWnd;
    } break;
    default:
      result = nullptr;
  };

  return result;
}

void CUIWindowMgr::PostQuit(CUIWindow *wnd) {
  if (wnd == m_selectCharWnd) {
    m_selectCharWnd = nullptr;
  }
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
  if (m_isInvalidatedByForce) {
    return;
  }

  m_isInvalidatedByForce = true;
  for (auto child : m_children) {
    if (child->IsUpdateNeeded()) {
      child->InvalidateChildren();
    }
  }
}

CUIWindow *CUIWindowMgr::GetCapture() { return m_captureWindow; }

void CUIWindowMgr::SetCapture(CUIWindow *window) { m_captureWindow = window; }

void CUIWindowMgr::ReleaseCapture() { m_captureWindow = nullptr; }

void CUIWindowMgr::SetFocusEdit(CUIWindow *window) {
  if (m_editWindow == window) {
    // Nothing to do
    return;
  }

  if (m_editWindow != nullptr) {
    m_editWindow->OnFinishEdit();
  }

  m_editWindow = window;
  if (m_editWindow != nullptr) {
    m_editWindow->OnBeginEdit();
  }
}

CUIWindow *CUIWindowMgr::GetFocusEdit() const { return m_editWindow; }

int CUIWindowMgr::ProcessInput() {
  const int x = g_Mouse->GetXPos();
  const int y = g_Mouse->GetYPos();

  if (m_modalWindow == nullptr) {
    for (auto quit_wnd : m_quit_window) {
      if (m_captureWindow != nullptr &&
          (m_captureWindow == quit_wnd ||
           m_captureWindow->IsChildOf(quit_wnd))) {
        m_captureWindow = nullptr;
      }

      if (m_editWindow != nullptr &&
          (m_editWindow == quit_wnd || m_editWindow->IsChildOf(quit_wnd))) {
        m_editWindow = nullptr;
      }

      if (m_modalWindow != nullptr &&
          (m_modalWindow == quit_wnd || m_modalWindow->IsChildOf(quit_wnd))) {
        m_modalWindow = nullptr;
      }

      if (m_last_hit_window != nullptr &&
          (m_last_hit_window == quit_wnd ||
           m_last_hit_window->IsChildOf(quit_wnd))) {
        m_last_hit_window = nullptr;
      }

      RemoveWindow(quit_wnd);
    }

    m_quit_window.clear();
  }

  if (m_captureWindow == nullptr) {
    CUIWindow *hit_window = nullptr;

    if (m_children.empty()) {
      hit_window = nullptr;
    } else {
      for (auto it = m_children.rbegin(); it != m_children.rend(); ++it) {
        hit_window = (*it)->HitTest(x, y);
        if (hit_window != nullptr && hit_window->IsShow()) {
          break;
        }
      }
    }

    if (m_modalWindow != nullptr) {
      if (hit_window == nullptr) {
      }
    }

    if (hit_window != nullptr) {
      int x_global, y_global;
      int x_local, y_local;

      hit_window->GetGlobalCoor(&x_global, &y_global);
      x_local = x - x_global;
      y_local = y - y_global;

      if (g_Mouse->GetLBtn() == CMouse::ButtonState::kDown) {
        hit_window->OnLBtnDown(x_local, y_local);
      } else if (g_Mouse->GetLBtn() == CMouse::ButtonState::kDbClick) {
        hit_window->OnLBtnDblClk(x - x_global, y - y_global);
      }

      if (g_Mouse->GetRBtn() == CMouse::ButtonState::kDown) {
        hit_window->OnRBtnDown(x_local, y_local);
      } else if (g_Mouse->GetRBtn() == CMouse::ButtonState::kDbClick) {
        hit_window->OnRBtnDblClk(x - x_global, y - y_global);
      }

      if (g_Mouse->GetWBtn() == CMouse::ButtonState::kDown) {
        hit_window->OnWBtnDown(x_local, y_local);
      }

      hit_window->OnMouseShape(x_local, y_local);
      if (m_last_mouse_x != x || m_last_mouse_y != y) {
        hit_window->OnMouseMove(x_local, y_local);
      } else {
        hit_window->OnMouseHover(x_local, y_local);
      }

      if (g_Mouse->GetWBtn() == CMouse::ButtonState::kUp) {
        hit_window->OnWBtnUp(x_local, y_local);
      }
      if (g_Mouse->GetRBtn() == CMouse::ButtonState::kUp) {
        hit_window->OnRBtnUp(x_local, y_local);
      }
      if (g_Mouse->GetLBtn() == CMouse::ButtonState::kUp) {
        hit_window->OnLBtnUp(x_local, y_local);
      }

      if (m_last_hit_window != nullptr && hit_window != m_last_hit_window) {
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

    if (g_Mouse->GetLBtn() == CMouse::ButtonState::kDown) {
    } else if (g_Mouse->GetLBtn() == CMouse::ButtonState::kDbClick) {
      m_captureWindow->OnLBtnDown(x_local, y_local);
      m_captureWindow->OnLBtnDblClk(x_local, y_local);
    }

    m_captureWindow->OnMouseShape(x_local, y_local);
    if (m_last_mouse_x != x || m_last_mouse_y != y) {
      m_captureWindow->OnMouseMove(x_local, y_local);
    } else {
      m_captureWindow->OnMouseHover(x_local, y_local);
    }

    // if (g_Mouse.m_wheel)
    //  m_captureWindow->OnWheel(g_mouse.m_wheel);
    if (g_Mouse->GetLBtn() == CMouse::ButtonState::kUp) {
      m_captureWindow->OnLBtnUp(x_local, y_local);
    }
  }

  if (m_editWindow != nullptr) {
    m_editWindow->Invalidate();
  }
  // g_mouseMoved = false;
  // if (x != m_lastMouseX || y != m_lastMouseY)
  //  g_mouseMoved = true;
  m_last_mouse_x = x;
  m_last_mouse_y = y;
  // if (!m_modalWindow)
  //  return rValue;

  return 1;
}

int CUIWindowMgr::ErrorMsg(const std::string &msg, int type, int isDefYes,
                           int changeMsg, unsigned int autoReturnTime) {
  LOG(error, "{}", msg);

  // Return 121 for now, to simulate a button push on "OK"
  return 121;
}

void CUIWindowMgr::SetCurScreen(int cur_screen) {
  switch (cur_screen) {
    case 110:
      // MakeSaveFileName(0);
      break;
    case 111:
      MakeWindow(WID_MAKECHARWND);
      break;
    case 120:
      // MakeSaveFileName(1);
      break;
  }
}

bool CUIWindowMgr::ProcessPushButton(SDL_Keycode key_code, int new_key_down,
                                     SDL_Scancode scan_code) {
  switch (key_code) {
    case SDLK_BACKSPACE:
      if (GetFocusEdit() != nullptr) {
        g_Language->OnChar('\b', 0);
      }
      break;
    case SDLK_RETURN:
      DefPushButton();
      return false;
      break;
    default:
      break;
  }

  return true;
}

bool CUIWindowMgr::IsFocusChatWnd() const {
  if (m_editWindow == m_chatWnd->common_chat() ||
      m_editWindow == m_chatWnd->whisper_chat()) {
    return true;
  }

  return false;
}

bool CUIWindowMgr::ExecuteMsgInBattleMode(SDL_Keycode virtual_key,
                                          int new_key_down) {
  return false;
}

void CUIWindowMgr::DefPushButton() const {
  for (auto &child : m_children) {
    child->SendMsg(nullptr, 0);
  }
}

void *CUIWindowMgr::SendMsg(int message, const void *val1, const void *val2,
                            const void *val3, const void *val4) {
  switch (message) {
    case 1: {
      if (m_chatWnd == nullptr) {
        return nullptr;
      }

      size_t color = reinterpret_cast<const size_t>(val2);
      if (color == 0) {
        color = 0xFFFFFF;
      }

      // if (strcmp((const char *)val1, aNoMsg_1) &&
      //    strcmp((const char *)val1, aNoMsg)) {
      m_chatWnd->SendMsg(nullptr, 37, val1,
                         reinterpret_cast<const void *>(color), val3, val4);
      //}
    } break;
    case 5:
      break;
  }

  return nullptr;
}

bool CUIWindowMgr::battle_mode() const { return m_battle_mode; }

void CUIWindowMgr::set_battle_mode(bool battle_mode) {
  m_battle_mode = battle_mode;
}
