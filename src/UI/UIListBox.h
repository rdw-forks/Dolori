#ifndef DOLORI_UI_UILISTBOX_H_
#define DOLORI_UI_UILISTBOX_H_

#include <string>
#include <vector>

#include "UI/UIScrollBar.h"
#include "UI/UIWindow.h"

class CUIListBox : public CUIWindow {
 public:
  CUIListBox(CUIWindowMgr* p_window_mgr);

  void OnLBtnDown(int x, int y) override;
  void* SendMsg(CUIWindow* sender, int message, const void* val1 = nullptr,
                const void* val2 = nullptr, const void* val3 = nullptr,
                const void* val4 = nullptr) override;
  void Resize(int cx, int cy) override;
  void OnCreate(int, int) override;
  void OnDraw() override;

  void Create2(int x, int y, int cx, int cy, bool trans);
  void SetColor(int r, int g, int b);
  void RecalcScrbarPos();
  size_t GetSelected() const;
  void AddItem(const std::string& text);

 protected:
  int InnerHitTest(int x, int y);

 protected:
  int m_bR;
  int m_bG;
  int m_bB;
  std::vector<std::string> m_items;
  size_t m_curItem;
  int m_vertViewOffset;
  int m_horzViewOffset;
  int m_maxTextWidth;
  int m_vertScrEnabled;
  int m_horzScrEnabled;
  CUIScrollBar* m_vertScrollBar;
  CUIScrollBar* m_horzScrollBar;
  bool m_isTransParent;
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
