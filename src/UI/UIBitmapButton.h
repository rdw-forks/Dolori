#ifndef DOLORI_UI_UIBITMAPBUTTON_H_
#define DOLORI_UI_UIBITMAPBUTTON_H_

#include <string>

#include "UI/UIButton.h"

class CUIBitmapButton : public CUIButton {
 public:
  CUIBitmapButton();
  ~CUIBitmapButton();

  void SetBitmapName(const std::string&, int);
  int GetBitmapWidth();
  int GetBitmapHeight();
  void OnDraw() override;

 private:
  int m_bitmapWidth;
  int m_bitmapHeight;
  std::string m_normalBitmapName;
  std::string m_mouseonBitmapName;
  std::string m_pressedBitmapName;
};

// class UIBitmapButton {
//  UIButton, offset = 0x0
//
//    public void UIBitmapButton(const class UIBitmapButton &)
//    public void UIBitmapButton::UIBitmapButton()
//    public void UIBitmapButton::~UIBitmapButton()
//    public void UIBitmapButton::OnDraw()
//    public void UIBitmapButton::SetBitmapName(const char *, int)
//    public int GetBitmapWidth()
//    public int GetBitmapHeight()
//    /* this+0x6c */ int m_bitmapWidth
//    /* this+0x70 */ int m_bitmapHeight
//    /* this+0x74 */ class std::string m_normalBitmapName
//
//    /* this+0x84 */ class std::string m_mouseonBitmapName
//
//    /* this+0x94 */ class std::string m_pressedBitmapName
//
//    public class UIBitmapButton & operator=(const class UIBitmapButton &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UIBITMAPBUTTON_H_
