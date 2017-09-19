#ifndef DOLORI_UI_UISCROLLBAR_H_
#define DOLORI_UI_UISCROLLBAR_H_

#include "UIWindow.h"

class CUIScrollBar : public CUIWindow {
 public:
  CUIScrollBar();
  ~CUIScrollBar();

  void SetPos(int);
  int GetPos();
  void SetVert(bool is_vertical);
  void SetType(int type);
  void SetRange(int range, size_t parentnumCanDisplayItem,
                size_t parentNumItem);
  int GetFixedLength();
  void Resize(int cx, int cy);
  void OnDraw();
  void OnLBtnDown(int x, int y);
  void OnLBtnUp(int x, int y);
  void OnMouseMove(int x, int y);

 protected:
  int HitTest(int x, int y);

 private:
  int m_drawMode;
  int m_maxPos;
  int m_curPos;
  bool m_isVert;
  int m_startDragX;
  int m_startDragY;
  int m_deltaDrag;
  size_t m_parentNumItem;
  size_t m_parentnumCanDisplayItem;
  int m_scrollBtnSize;
  int m_fixedLength;
  int m_type;
};

// class UIScrollBar {
//  UIWindow,
//      offset = 0x0
//
//               public void
//               UIScrollBar(const class UIScrollBar &) public void
//               UIScrollBar::UIScrollBar() public void
//                   UIScrollBar::~UIScrollBar() public void
//                   UIScrollBar::Create(int, int, int, int) public void
//                   UIScrollBar::OnLBtnDown(int, int) public void
//                   UIScrollBar::OnLBtnDblClk(int, int) public void
//                   UIScrollBar::OnMouseMove(int, int) public void
//                   UIScrollBar::OnMouseShape(int, int) public void
//                   UIScrollBar::OnLBtnUp(int, int) public void
//                   UIScrollBar::OnRBtnUp(int, int) public void
//                   UIScrollBar::OnWheel(int) public void
//                   UIScrollBar::OnDraw() public void
//                   UIScrollBar::Resize(int, int) public unsigned char
//                   UIScrollBar::IsTransmitMouseInput() public int
//                   UIScrollBar::GetThumbSize() public void
//                   UIScrollBar::SetRange(int, int, int) public void
//                   UIScrollBar::SetPos(int) public void
//                   SetType(int) public int
//                   UIScrollBar::GetPos() protected int
//                   UIScrollBar::HitTest(int, int) protected int
//                   UIScrollBar::GetScrollRange() protected int
//                   UIScrollBar::GetThumbOffset() int m_drawMode int m_maxPos
//                   int
//                       m_curPos int m_isVert int m_startDragX int
//                           m_startDragY int m_deltaDrag int m_parentNumItem
//                           int
//                               m_parentnumCanDisplayItem int m_scrollBtnSize
//                               int
//                                   m_fixedLength int m_type public class
//               UIScrollBar &
//               operator=(const class UIScrollBar &) public void
//                   __local_vftable_ctor_closure() public void *
//                   __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UISCROLLBAR_H_