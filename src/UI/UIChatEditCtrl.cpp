#include "UI/UIChatEditCtrl.h"

#include "Common/Globals.h"
#include "Core/UIWindowMgr.h"

CUIChatEditCtrl::CUIChatEditCtrl(CUIWindowMgr *p_window_mgr)
    : CUIEditCtrl(p_window_mgr) {}

void CUIChatEditCtrl::OnLBtnDown(int x, int y) {
  if (!p_window_mgr_->battle_mode()) {
    p_window_mgr_->SetFocusEdit(this);
  }

  m_parent->OnLBtnDown(x + m_x, y + m_y);
}

void *CUIChatEditCtrl::SendMsg(CUIWindow *sender, int message, const void *val1,
                               const void *val2, const void *val3,
                               const void *val4) {
  switch (message) {
    case 19:
      // TODO(LinkZ)
      break;
    case 18:
      // TODO(LinkZ)
      break;
    case 0:
      CUIWindow::SendMsg(sender, message, val1, val2, val3, val4);
      g_Language->ResetInput();
      break;
    default:
      CUIWindow::SendMsg(sender, message, val1, val2, val3, val4);
      break;
  }

  return nullptr;
}
