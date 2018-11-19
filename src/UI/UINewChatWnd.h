#ifndef DOLORI_UI_UINEWCHATWND_H_
#define DOLORI_UI_UINEWCHATWND_H_

#include "UI/UIChatHisBox.h"
#include "UI/UIFrameWnd.h"

class CUINewChatWnd : public CUIFrameWnd {
 public:
  CUINewChatWnd(CUIWindowMgr *p_window_mgr);

  void OnCreate(int x, int y) override;
  void OnDraw() override;
  void *SendMsg(CUIWindow *, int, const void *val1 = nullptr,
                const void *val2 = nullptr, const void *val3 = nullptr,
                const void *val4 = nullptr) override;

 private:
  CUIChatHisBox *list_box_;
  CUIChatHisBox *cmd_list_box_;
  size_t title_height_;
  size_t title_width_;
  size_t chat_edit_height_;
};

// class UINewChatWnd {
//	UIFrameWnd, offset = 0x0
//
//		public void UINewChatWnd(const class UINewChatWnd &)
//		public void UINewChatWnd::UINewChatWnd()
//		public void UINewChatWnd::~UINewChatWnd()
//		public void UINewChatWnd::OnCreate(int, int)
//		public void UINewChatWnd::OnDraw()
//		public void UINewChatWnd::OnDraw2()
//		public void UINewChatWnd::OnLBtnDown(int, int)
//		public void UINewChatWnd::OnMouseMove(int, int)
//		public void UINewChatWnd::OnLBtnUp(int, int)
//		public int UINewChatWnd::SendMsg(class UIWindow *, int, int,
// int,
// int, int) 		public unsigned char
// UINewChatWnd::GetTransBoxInfo2(struct BOXINFO
//*) 		public void UINewChatWnd::DrawBoxScreen2() 		public
// void
// UINewChatWnd::Move(int, int) 		public void
// UINewChatWnd::Resize(int,
// int) 		public void UINewChatWnd::StoreInfo() 		public
// void UINewChatWnd::SetShow(int) 		public void
// UINewChatWnd::SetState(int) public int GetState() 		public void
// UINewChatWnd::WriteChatToFile() 		public void
// WriteChatToReportFile() public void UINewChatWnd::ChangeTab()
// public void UINewChatWnd::StickOnOff(unsigned char)
//		/* this+0x60 */ class UIEditCtrl * m_lastFocusChat
//		/* this+0x64 */ class UIResizer * m_resizer
//		/* this+0x68 */ class UIChatEditCtrl * m_commonChat
//		/* this+0x6c */ class UIWhisperEditCtrl * m_whisperChat
//		/* this+0x70 */ struct BOXINFO m_boxInfo
//
//		/* this+0x8c */ class UIBitmapButton *[0x4] m_buttons
//		/* this+0x9c */ int m_comboMode
//		/* this+0xa0 */ class UIChatHisBox * m_listBox
//		/* this+0xa4 */ class UIChatHisBox * m_cmdListBox
//		/* this+0xa8 */ int m_tab
//		/* this+0xac */ int m_saveState
//		/* this+0xb0 */ int m_titleHeight
//		/* this+0xb4 */ int m_titleWidth
//		/* this+0xb8 */ int m_chatEditHeight
//		/* this+0xbc */ class UIBitmapButton * m_btnStickOff
//		/* this+0xc0 */ class UIBitmapButton * m_btnOption
//		/* this+0xc4 */ unsigned long m_colorTab1
//		/* this+0xc8 */ unsigned long m_colorTab2
//		public class UINewChatWnd & operator=(const class UINewChatWnd
//&) 		public void __local_vftable_ctor_closure() 		public
// void *
//__vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UINEWCHATWND_H_
