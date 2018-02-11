#include "UIButton.h"
#include "Common/Globals.h"

CUIButton::CUIButton() {}

CUIButton::~CUIButton() {}

void CUIButton::OnLBtnDown(int x, int y) {
  if (!m_isDisabled) {
    g_WindowMgr->SetCapture(this);
    m_state = 2;
    Invalidate();
  }
}

void CUIButton::OnLBtnUp(int x, int y) {
  if (!m_isDisabled && g_WindowMgr->GetCapture() == this) {
    if (x < 0 || x >= m_w || y < 0 || y >= m_h) {
      m_state = 0;
    } else {
      m_state = 1;

      if (m_parent)
        m_parent->SendMsg(this, 6, (void*)m_id, 0, 0, 0);
      else
        g_ModeMgr->GetCurMode()->SendMsg(0, (void*)m_id, 0, 0);
    }
    Invalidate();
    g_WindowMgr->ReleaseCapture();
  }
}

void CUIButton::OnMouseMove(int x, int y) {
  int state;

  if (!m_isDisabled) {
    if (g_WindowMgr->GetCapture() == this) {
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
