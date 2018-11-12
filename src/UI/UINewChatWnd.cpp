#include "UI/UINewChatWnd.h"

CUINewChatWnd::CUINewChatWnd(CUIWindowMgr *p_window_mgr)
    : CUIFrameWnd(p_window_mgr),
      list_box_(),
      cmd_list_box_(),
      title_height_(16),
      title_width_(71),
      chat_edit_height_(24) {}

void CUINewChatWnd::OnCreate(int x, int y) {
  list_box_ = new CUIChatHisBox(p_window_mgr_);
  if (list_box_ != nullptr) {
    list_box_->Create2(0, 0, m_w - 8, 70, false);

    if (y - 70 < chat_edit_height_ + title_height_) {
      list_box_->Move(5, -70);
    } else {
      list_box_->Move(5, title_height_ + 2);
    }

    list_box_->SetId(118);
    AddChild(list_box_);
  }
}

void *CUINewChatWnd::SendMsg(CUIWindow *sender, int message, const void *val1,
                             const void *val2, const void *val3,
                             const void *val4) {
  switch (message) {
    case 37:
      if (list_box_ != nullptr) {
        const auto chat_msg = static_cast<const char *>(val1);
        list_box_->AddItem(chat_msg);
      }
      break;
    default:
      return CUIFrameWnd::SendMsg(sender, message, val1, val2, val3, val4);
  }

  return nullptr;
}
