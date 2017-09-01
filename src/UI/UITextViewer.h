#ifndef DOLORI_UI_UITEXTVIEWER_H_
#define DOLORI_UI_UITEXTVIEWER_H_

#include "UIListBox.h"

class CUITextViewer : public CUIListBox {
 public:
  CUITextViewer();
  ~CUITextViewer();

  void OnCreate(int cx, int cy);
  void Create2(int x, int y, int cx, int cy, bool trans);
  void OnDraw();

 private:
  int m_bgR;
  int m_bgG;
  int m_bgB;
  bool m_isTransParent;
};

//class UITextViewer {
//  UIListBox, offset = 0x0
//
//                      public void
//                      UITextViewer(const class UITextViewer &) public void
//                      UITextViewer::UITextViewer() public void
//                          UITextViewer::~UITextViewer() public void
//                          UITextViewer::Create2(int, int, int, int,
//                                                unsigned char) public void
//                          UITextViewer::OnCreate(int, int) public void
//                          UITextViewer::OnLBtnDown(int, int) public void
//                          UITextViewer::OnLBtnDblClk(int, int) public void
//                          UITextViewer::OnLBtnUp(int, int) public void
//                          UITextViewer::OnDraw() public int
//                          UITextViewer::SendMsg(class UIWindow *, int, int, int,
//                                                int, int)
//                      /* this+0x90 */ int m_bgR
//                      /* this+0x94 */ int m_bgG
//                      /* this+0x98 */ int m_bgB public class UITextViewer &
//                      operator=(const class UITextViewer &) public void
//                          __local_vftable_ctor_closure() public void *
//                          __vecDelDtor(unsigned int)
//}

#endif // DOLORI_UI_UITEXTVIEWER_H_
