#ifndef DOLORI_UI_WHISPEREDITCTRL_H_
#define DOLORI_UI_WHISPEREDITCTRL_H_

#include <string>
#include <vector>

#include "UI/UIEditCtrl.h"

class CUIWhisperEditCtrl : public CUIEditCtrl {
  std::vector<std::string> chat_history_;
  int current_history_;
};

// class UIWhisperEditCtrl {
//	UIEditCtrl, offset = 0x0
//
//		public void UIWhisperEditCtrl(const class UIWhisperEditCtrl &)
//		public void UIWhisperEditCtrl::UIWhisperEditCtrl()
//		public void UIWhisperEditCtrl::OnBeginEdit()
//		public void UIWhisperEditCtrl::OnFinishEdit()
//		public void UIWhisperEditCtrl::SetText(const char *)
//		public int UIWhisperEditCtrl::SendMsg(class UIWindow *, int,
// int, int, int, int) 		public void UIWhisperEditCtrl::StoreInHistory()
//		/* this+0x90 */ class std::vector<std::string,
// std::allocator<std::string > > m_hisChat
//
//		/* this+0xa0 */ int m_curHis
//		public class UIWhisperEditCtrl & operator=(const class
// UIWhisperEditCtrl &) 		public void
// UIWhisperEditCtrl::~UIWhisperEditCtrl() 		public void
//__local_vftable_ctor_closure() 		public void *
//__vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_WHISPEREDITCTRL_H_
