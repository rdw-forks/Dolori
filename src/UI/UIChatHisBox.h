#ifndef DOLORI_UI_UICHATHISBOX_H_
#define DOLORI_UI_UICHATHISBOX_H_

#include "UI/UIListBox.h"

class CUIChatHisBox : public CUIListBox {
 public:
  CUIChatHisBox(CUIWindowMgr *p_window_mgr);

  void OnCreate(int x, int y) override;
  void OnDraw() override;

  void AddItem(const std::string &message, uint32_t color);

 private:
  std::vector<std::string> talker_names_;
  std::vector<uint32_t> item_colors_;
  size_t max_items_;
};

// class UIChatHisBox {
//	UIListBox, offset = 0x0
//
//		public void UIChatHisBox(const class UIChatHisBox &)
//		public void UIChatHisBox::UIChatHisBox()
//		public void UIChatHisBox::~UIChatHisBox()
//		public void UIChatHisBox::Create2(int, int, int, int, unsigned
// char) 		public void UIChatHisBox::OnCreate(int, int)
// public void UIChatHisBox::OnLBtnDown(int, int) 		public void
// UIChatHisBox::OnLBtnDblClk(int, int) 		public void
// UIChatHisBox::OnLBtnUp(int, int) 		public void
// UIChatHisBox::OnDraw() 		public int UIChatHisBox::SendMsg(class
// UIWindow *, int, int, int, int, int) 		public unsigned char
// UIChatHisBox::IsTransmitMouseInput() 		public void
// UIChatHisBox::AddItem(const
// char *, unsigned long, const char *) 		public void
// UIChatHisBox::ClearAllItems() 		public void
// UIChatHisBox::Resize(int, int) 		public void
// UIChatHisBox::SetShow(int) 		public void
// UIChatHisBox::DeleteFirstHalfItem() 		public unsigned long
// GetItemColor(int) 		public int
// UIChatHisBox::WriteChatToReportFile(const char *) 		public int
// UIChatHisBox::WriteChatToFile(const char *) 		public void
// UIChatHisBox::AddItem2(const char *, unsigned long, const char *)
// protected const char * UIChatHisBox::GetTalkerName(int)
//		/* this+0x90 */ class std::vector<std::string,
// std::allocator<std::string > > m_talkerNameList
//
//		/* this+0xa0 */ class std::vector<unsigned long,
// std::allocator<unsigned long> > m_itemColors
//
//		/* this+0xb0 */ int m_maxItem
//		public class UIChatHisBox & operator=(const class UIChatHisBox
//&) 		public void __local_vftable_ctor_closure() 		public
// void *
//__vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UICHATHISBOX_H_
