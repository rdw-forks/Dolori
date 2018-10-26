#ifndef DOLORI_UI_UIBUTTON_H_
#define DOLORI_UI_UIBUTTON_H_

#include <string>

#include "UI/UIWindow.h"

class CUIButton : public CUIWindow {
 public:
  CUIButton(CUIWindowMgr* p_window_mgr);

  void OnLBtnDown(int, int);
  void OnLBtnUp(int, int);
  void OnMouseMove(int, int);
  void OnMouseHover(int, int);

 protected:
  std::string m_text;
  std::string m_toolTip;
  int m_isDisabled;
};

// class UIButton {
//  UIWindow, offset = 0x0
//
//    public void UIButton(const class UIButton &)
//    public void UIButton::UIButton()
//    public void UIButton::~UIButton()
//    public void UIButton::OnLBtnDblClk(int, int)
//    public void UIButton::OnLBtnDown(int, int)
//    public void UIButton::OnMouseMove(int, int)
//    public void UIButton::OnLBtnUp(int, int)
//    public void UIButton::OnMouseShape(int, int)
//    public void UIButton::OnDraw()
//    public void UIButton::OnMouseHover(int, int)
//    public void UIButton::SetToolTip(const char *)
//    public void UIButton::SetText(class std::string)
//    public void SetDiabled(int)
//    /* this+0x48 */ class std::string m_text
//
//    /* this+0x58 */ class std::string m_toolTip
//
//    /* this+0x68 */ int m_isDisabled
//    public class UIButton & operator=(const class UIButton &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UIBUTTON_H_
