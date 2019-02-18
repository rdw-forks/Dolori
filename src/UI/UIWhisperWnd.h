#ifndef DOLORI_UI_UIWHISPERWND_H_
#define DOLORI_UI_UIWHISPERWND_H_

#include <string>
#include <vector>

#include "UI/UIBitmapButton.h"
#include "UI/UIChatEditCtrl.h"
#include "UI/UIFrameWnd.h"

class CUIWhisperWnd : public CUIFrameWnd {
 private:
  std::string m_whisperName;
  std::string m_whisperTitle;
  class UIResizer* m_resizer;
  CUIChatEditCtrl* m_chatEdit;
  class UIChatHisBox2* m_listBox;
  CUIBitmapButton* m_sysButton;
  // std::vector<StringId> m_menuItems;
  struct WhisperWndInfo* m_info;
};

// class UIWhisperWnd {
//	UIFrameWnd, offset = 0x0
//
//		public void UIWhisperWnd(const class UIWhisperWnd &)
//		public void UIWhisperWnd::UIWhisperWnd()
//		public void UIWhisperWnd::~UIWhisperWnd()
//		public void UIWhisperWnd::OnCreate(int, int)
//		public void UIWhisperWnd::OnDraw()
//		public void UIWhisperWnd::OnRBtnUp(int, int)
//		public int UIWhisperWnd::SendMsg(class UIWindow *, int, int,
// int,
// int, int) 		public void UIWhisperWnd::StoreInfo() 		public
// void UIWhisperWnd::Move(int, int) 		public void
// UIWhisperWnd::WriteChatToFile() 		public void
// UIWhisperWnd::WriteChatToReportFile()
//		/* this+0x60 */ class std::string m_whisperName
//
//		/* this+0x70 */ class std::string m_whisperTitle
//
//		/* this+0x80 */ class UIResizer * m_resizer
//		/* this+0x84 */ class UIChatEditCtrl * m_chatEdit
//		/* this+0x88 */ class UIChatHisBox2 * m_listBox
//		/* this+0x8c */ class UIBitmapButton * m_sysButton
//		/* this+0x90 */ class std::vector<StringId,
// std::allocator<StringId> > m_menuItems
//
//		/* this+0xa0 */ struct WhisperWndInfo * m_info
//		public class UIWhisperWnd & operator=(const class UIWhisperWnd
//&) 		public void __local_vftable_ctor_closure() 		public
// void *
//__vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UIWHISPERWND_H_
