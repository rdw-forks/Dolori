#include "UI/UINewChatWnd.h"

#include "Common/Globals.h"
#include "Common/const_strings.h"
#include "Common/debug.h"
#include "UI/UIBmp.h"

CUINewChatWnd::CUINewChatWnd(CUIWindowMgr *p_window_mgr)
    : CUIFrameWnd(p_window_mgr),
      common_chat_(),
      list_box_(),
      cmd_list_box_(),
      title_height_(16),
      title_width_(71),
      chat_edit_height_(24) {}

CUIChatEditCtrl *const CUINewChatWnd::common_chat() const {
  return common_chat_;
}

CUIWhisperEditCtrl *const CUINewChatWnd::whisper_chat() const {
  return whisper_chat_;
}

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

  common_chat_ = new CUIChatEditCtrl(p_window_mgr_);
  if (common_chat_ == nullptr) {
    return;
  }

  common_chat_->Create(460, 16);
  common_chat_->Move(110, m_h - chat_edit_height_ + 4);
  common_chat_->SetTextLimit(70);
  common_chat_->SetFrameColor(240, 240, 240);
  AddChild(common_chat_);

  m_defPushId = 118;
}

void CUINewChatWnd::OnDraw() {
  ClearDC(0);

  if (m_h > title_height_ + chat_edit_height_) {
    DrawBox(3, title_height_, 1, m_h - title_height_ - chat_edit_height_,
            0xFFFFFFFF);
    // TODO(LinkZ): Implement chat box tabs (the code below should be
    // uncommented once this is done)
    // DrawBox(2 * title_width_ + 3, title_height_, m_w - (2 * title_width_ +
    // 10), 1, 0xFFFFFFFF);
    DrawBox(4, title_height_, m_w - 10, 1, 0xFFFFFFFF);
    DrawBox(m_w - 6, title_height_, 1, 1, 0xFF8E8E8E);
    DrawBox(m_w - 5, title_height_ + 1, 1, 1, 0xFF8E8E8E);
    DrawBox(m_w - 4, title_height_ + 2, 1,
            m_h - chat_edit_height_ - title_height_ - 2, 0xFF8E8E8E);
  }

  if (p_window_mgr_->battle_mode()) {
    const std::string dialog_bg =
        const_strings::kResourceSubfolder + "basic_interface/dialog_bg2.bmp";
    auto bitmap =
        static_cast<CBitmapRes *>(g_ResMgr->Get(UIBmp(dialog_bg), false));
    DrawBitmap(0, m_h - bitmap->GetHeight(), bitmap, 0);
  } else {
    const std::string dialog_bg =
        const_strings::kResourceSubfolder + "basic_interface/dialog_bg.bmp";
    auto bitmap =
        static_cast<CBitmapRes *>(g_ResMgr->Get(UIBmp(dialog_bg), false));
    DrawBitmap(0, m_h - bitmap->GetHeight(), bitmap, 0);
  }
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
      // Add a message to the history
      if (list_box_ != nullptr) {
        const auto chat_msg = static_cast<const char *>(val1);
        const auto color = reinterpret_cast<size_t>(val2);
        list_box_->AddItem(chat_msg, color);
      }
      break;
    case 6: {
      const auto child_id = reinterpret_cast<size_t>(val1);
      switch (child_id) {
        case 118: {
          // Process chat message
          Invalidate();
          const std::string text_msg = common_chat_->GetText();
          if (text_msg.empty()) {
            if (!p_window_mgr_->battle_mode()) {
              p_window_mgr_->set_battle_mode(true);
              p_window_mgr_->SetFocusEdit(nullptr);
              common_chat_->SetShow(false);
            } else {
              p_window_mgr_->set_battle_mode(false);
              p_window_mgr_->SetFocusEdit(common_chat_);
              common_chat_->SetShow(true);
            }

            break;
          }

          // common_chat_->StoreInHistory()
          common_chat_->SetText("");
          if (text_msg.length() > 1 && text_msg[0] == '/') {
            TALKTYPE talk_type = {};
            const int result =
                g_Session->GetTalkType(text_msg, &talk_type, nullptr);
            if (result == -1) {
              g_ModeMgr->GetCurMode()->SendMsg(
                  MM_PROCESS_TALK_TYPE, reinterpret_cast<void *>(talk_type));
              break;
            }
          }

          g_ModeMgr->GetCurMode()->SendMsg(
              MM_CHATMSG, reinterpret_cast<const void *>(text_msg.c_str()));
        } break;
      }
    } break;
    default:
      return CUIFrameWnd::SendMsg(sender, message, val1, val2, val3, val4);
  }

  return nullptr;
}
