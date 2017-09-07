#ifndef DOLORI_UI_UILISTBOX_H_
#define DOLORI_UI_UILISTBOX_H_

#include <string>
#include <vector>
#include "UIScrollBar.h"
#include "UIWindow.h"

class CUIListBox : public CUIWindow {
 public:
  CUIListBox();
  ~CUIListBox();

  void Resize(int cx, int cy);
  void RecalcScrbarPos();
  void OnCreate(int, int);
  void AddItem(const char*);
  int SendMsg(CUIWindow* sender, int message, int val1, int val2, int val3,
              int val4);

 protected:
  // int HitTest(int, int);

 protected:
  int m_bR;
  int m_bG;
  int m_bB;
  std::vector<std::string> m_items;
  int m_curItem;
  int m_vertViewOffset;
  int m_horzViewOffset;
  int m_maxTextWidth;
  int m_vertScrEnabled;
  int m_horzScrEnabled;
  CUIScrollBar* m_vertScrollBar;
  CUIScrollBar* m_horzScrollBar;
  int m_isTransParent;
  int m_itemSpacing;
  char m_noColor;
};

// class UIListBox {
//  UIWindow, offset = 0x0
//
//    public void UIListBox(const class UIListBox &)
//    public void UIListBox::UIListBox()
//    public void UIListBox::~UIListBox()
//    public void UIListBox::Create2(int, int, int, int, unsigned char)
//    public void UIListBox::OnCreate(int, int)
//    public void UIListBox::OnLBtnDown(int, int)
//    public void UIListBox::OnLBtnDblClk(int, int)
//    public void UIListBox::OnWheel(int)
//    public void UIListBox::OnDraw()
//    public int UIListBox::SendMsg(class UIWindow *, int, int, int, int, int)
//    public void UIListBox::AddItem(const char *)
//    public void UIListBox::ClearAllItems()
//    public void UIListBox::Resize(int, int)
//    public void UIListBox::RecalcScrbarPos()
//    public int IsVertScrEnabled()
//    public int GetSelected()
//    public int GetNumItem()
//    public class std::string & GetItem(int)
//     int m_bR
//     int m_bG
//     int m_bB
//    protected int UIListBox::HitTest(int, int)
//     class std::vector<std::string, std::allocator<std::string
//    > > m_items
//
//     int m_curItem
//     int m_vertViewOffset
//     int m_horzViewOffset
//     int m_maxTextWidth
//     int m_vertScrEnabled
//     int m_horzScrEnabled
//     class UIScrollBar * m_vertScrollBar
//     class UIScrollBar * m_horzScrollBar
//     int m_isTransParent
//     int m_itemSpacing
//     char m_noColor
//    public class UIListBox & operator=(const class UIListBox &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UILISTBOX_H_