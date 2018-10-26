#include "UI/UIButton.h"

#include "Common/Globals.h"

CUIButton::CUIButton(CUIWindowMgr* p_window_mgr)
    : CUIWindow(p_window_mgr), m_isDisabled() {}

void CUIButton::OnLBtnDown(int x, int y) {
  if (!m_isDisabled) {
    p_window_mgr_->SetCapture(this);
    m_state = 2;
    Invalidate();
  }
}

void CUIButton::OnLBtnUp(int x, int y) {
  if (!m_isDisabled && p_window_mgr_->GetCapture() == this) {
    if (x < 0 || x >= m_w || y < 0 || y >= m_h) {
      m_state = 0;
    } else {
      m_state = 1;

      if (m_parent) {
        m_parent->SendMsg(this, WM_BUTTON_PRESSED,
                          reinterpret_cast<void*>(m_id));
      } else {
        g_ModeMgr->GetCurMode()->SendMsg(MM_COMMAND,
                                         reinterpret_cast<void*>(m_id));
      }
    }

    Invalidate();
    p_window_mgr_->ReleaseCapture();
  }
}

void CUIButton::OnMouseMove(int x, int y) {
  int state;

  if (!m_isDisabled) {
    if (p_window_mgr_->GetCapture() == this) {
      if (x >= 0 && x < m_w && y >= 0 && y < m_h) {
        state = 2;
        if (m_state != state) {
          m_state = state;
          Invalidate();
        }
        return;
      }
      if (m_state) {
        m_state = 0;
        Invalidate();
      }
    } else {
      if (x >= 0 && x < m_w && y >= 0 && y < m_h) {
        state = 1;
        if (m_state != state) {
          m_state = state;
          Invalidate();
        }
        return;
      }
      if (m_state) {
        m_state = 0;
        Invalidate();
      }
    }
  }
}

void CUIButton::OnMouseHover(int x, int y) {
  if (!m_isDisabled) {
    OnMouseMove(x, y);
    if (m_toolTip.length()) {
      GetGlobalCoor(&x, &y);
      y -= 20;
      // if (!m_toolTip.data())
      // CMode::MakeHelpBalloon(g_modeMgr.m_curMode, "", x, y, 0xFFFFFFFF);
    }
  }
}
