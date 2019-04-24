#ifndef DOLORI_UI_UICHATEDITCTRL_H_
#define DOLORI_UI_UICHATEDITCTRL_H_

#include <string>
#include <vector>

#include "UI/UIEditCtrl.h"

class CUIChatEditCtrl : public CUIEditCtrl {
 public:
  CUIChatEditCtrl(CUIWindowMgr *p_window_mgr);

  void OnLBtnDown(int x, int y) override;
  void *SendMsg(CUIWindow *sender, int message, const void *val1 = nullptr,
                const void *val2 = nullptr, const void *val3 = nullptr,
                const void *val4 = nullptr) override;

 private:
  /*std::vector<std::string> chat_history_;
  std::string last_edit_text_;
  size_t current_history_;*/
};

// class UIChatEditCtrl {
//	UIEditCtrl, offset = 0x0
//
//		public void UIChatEditCtrl(const class UIChatEditCtrl &)
//		public void UIChatEditCtrl::UIChatEditCtrl()
//		public int UIChatEditCtrl::SendMsg(class UIWindow *, int, int,
// int, int, int) 		public void UIChatEditCtrl::OnLBtnDown(int, int)
// public void UIChatEditCtrl::StoreInHistory()
//		/* this+0x90 */ class std::vector<std::string,
// std::allocator<std::string > > m_hisChat
//
//		/* this+0xa0 */ class std::string m_lastEditText
//
//		/* this+0xb0 */ int m_curHis
//		public class UIChatEditCtrl & operator=(const class
// UIChatEditCtrl
//&) 		public void UIChatEditCtrl::~UIChatEditCtrl() public void
//__local_vftable_ctor_closure() 		public void *
//__vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UICHATEDITCTRL_H_
