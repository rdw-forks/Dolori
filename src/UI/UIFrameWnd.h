#ifndef DOLORI_UI_UIFRAMEWND_H_
#define DOLORI_UI_UIFRAMEWND_H_

#include "UI/UIWindow.h"

class CUIFrameWnd : public CUIWindow {
 public:
  CUIFrameWnd(CUIWindowMgr *p_window_mgr);

  void OnLBtnDown(int, int);
  void OnLBtnUp(int x, int y);
  void *SendMsg(CUIWindow *, int, void *val1 = nullptr, void *val2 = nullptr,
                void *val3 = nullptr, void *val4 = nullptr) override;

 protected:
  int m_startGlobalX;
  int m_startGlobalY;
  int m_orgX;
  int m_orgY;
  int m_defPushId;
  int m_defCancelPushId;
};

// class UIFrameWnd {
//  UIWindow, offset = 0x0
//
//    public void UIFrameWnd(const class UIFrameWnd &)
//    public void UIFrameWnd::UIFrameWnd()
//    public void UIFrameWnd::~UIFrameWnd()
//    public void UIFrameWnd::OnLBtnDown(int, int)
//    public void UIFrameWnd::OnMouseMove(int, int)
//    public void UIFrameWnd::OnMouseHover(int, int)
//    public void UIFrameWnd::OnLBtnUp(int, int)
//    public void UIFrameWnd::Move(int, int)
//    public unsigned char UIFrameWnd::IsFrameWnd()
//    public void UIFrameWnd::SaveOriginalPos()
//    public void UIFrameWnd::MoveDelta(int, int)
//    public int UIFrameWnd::SendMsg(class UIWindow *, int, int, int, int, int)
//    public void UIFrameWnd::RefreshSnap()
//    protected void UIFrameWnd::DrawItem(int, int, const char *, unsigned char)
//    protected void UIFrameWnd::DrawItem(int, int, const struct ITEM_INFO &,
//    unsigned char) protected void UIFrameWnd::DrawItemWithCount(int, int,
//    const struct ITEM_INFO &, unsigned char, unsigned char) protected void
//    UIFrameWnd::DrawItemFrame(int, int) protected void
//    UIFrameWnd::DrawLatticeFrame(int, int, int, int) protected int
//    UIFrameWnd::MakeItemText(const struct ITEM_INFO &, unsigned long &, class
//    std::vector<char const *, std::allocator<char const *> > &, char * &, char
//    * &, unsigned char) protected int UIFrameWnd::TextOutWithItemRect(int,
//    int, int, class std::vector<char const *, std::allocator<char const *> >
//    &, char *, char *, unsigned long, unsigned long, int, int) protected int
//    UIFrameWnd::DrawItemText(int, int, const struct ITEM_INFO &, unsigned
//    long, int, int) protected int UIFrameWnd::DrawItemTextRect(int, int, int,
//    const struct ITEM_INFO &, unsigned long, int, int) protected int
//    UIFrameWnd::DrawItemObtainTextRect(int, int, int, const struct ITEM_INFO
//    &, unsigned long, int, int)
//     int m_startGlobalX
//     int m_startGlobalY
//     int m_orgX
//     int m_orgY
//     int m_defPushId
//     int m_defCancelPushId
//    public class UIFrameWnd & operator=(const class UIFrameWnd &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UIFRAMEWND_H_
