#include "UI/UINewChatWnd.h"

#include "Common/Globals.h"
#include "Common/const_strings.h"
#include "UI/UIBmp.h"

CUINewChatWnd::CUINewChatWnd(CUIWindowMgr *p_window_mgr)
    : CUIFrameWnd(p_window_mgr),
      list_box_(),
      cmd_list_box_(),
      title_height_(16),
      title_width_(71),
      chat_edit_height_(24) {}

void CUINewChatWnd::OnCreate(int x, int y) {
  if (y > chat_edit_height_) {
    m_state = (y - (title_height_ + m_state + 74)) / 42 + 1;
    if (m_state > 4) {
      m_state = 4;
    }
  } else {
    m_state = 0;
  }

  list_box_ = new CUIChatHisBox(p_window_mgr_);
  if (list_box_ == nullptr) {
    return;
  }

  list_box_->Create2(0, 0, m_w - 8, 60, true);
  // if (y - 70 < chat_edit_height_ + title_height_) {
  //  list_box_->Move(5, -70);
  //} else {
  list_box_->Move(5, title_height_);
  //}

  list_box_->SetId(118);
  AddChild(list_box_);
}

void CUINewChatWnd::OnDraw() {
  ClearDC(0);

  if (m_h > title_height_ + chat_edit_height_) {
    DrawBox(3, title_height_, 1, m_h - title_height_ - chat_edit_height_,
            0xFFFFFFFF);
    DrawBox(2 * title_width_ + 3, title_height_, m_w - (2 * title_width_ + 10),
            1, 0xFFFFFFFF);
    DrawBox(m_w - 6, title_height_, 1, 1, 0xFF8E8E8E);
    DrawBox(m_w - 5, title_height_ + 1, 1, 1, 0xFF8E8E8E);
    DrawBox(m_w - 4, title_height_ + 2, 1,
            m_h - chat_edit_height_ - title_height_ - 2, 0xFF8E8E8E);
  }

  const std::string scroll_mid =
      const_strings::kResourceSubfolder + "basic_interface/dialog_bg.bmp";
  auto bitmap =
      static_cast<CBitmapRes *>(g_ResMgr->Get(UIBmp(scroll_mid), false));
  DrawBitmap(0, m_h - bitmap->GetHeight(), bitmap, 0);
}

void *CUINewChatWnd::SendMsg(CUIWindow *sender, int message, const void *val1,
                             const void *val2, const void *val3,
                             const void *val4) {
  switch (message) {
    case 34:
      // TODO(LinkZ): Check saved settings and restore them if possible
      m_x = 0;
      m_y = g_Renderer->GetHeight() - m_h;
      // SetState(state);
      Move(m_x, m_y);
      break;
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
