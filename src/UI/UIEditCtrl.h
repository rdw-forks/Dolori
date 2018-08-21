#ifndef DOLORI_UI_UIEDITCTRL_H_
#define DOLORI_UI_UIEDITCTRL_H_

#include <string>

#include "UI/UIWindow.h"

class CUIEditCtrl : public CUIWindow {
 public:
  CUIEditCtrl();
  ~CUIEditCtrl();

  void HideChars(bool);
  void SetFrameColor(int r, int g, int b);
  void OnLBtnDown(int x, int y);
  void OnDraw();
  void DrawEditText();
  void OnBeginEdit();
  void OnFinishEdit();
  void RefreshText();
  const char* GetText();

 private:
  size_t m_selectionOrigin;
  size_t m_selectionCursor;
  bool m_maskchar;
  int m_maxchar;
  int m_isSingColorFrame;
  int m_r;
  int m_g;
  int m_b;
  int m_textR;
  int m_textG;
  int m_textB;
  uint32_t m_text_color;
  int m_xOffset;
  int m_yOffset;
  int m_type;
  std::string m_text;
};

// class UIEditCtrl {
//  UIWindow, offset = 0x0
//
//    public void UIEditCtrl(const class UIEditCtrl &)
//    public void UIEditCtrl::UIEditCtrl()
//    public void UIEditCtrl::~UIEditCtrl()
//    public void UIEditCtrl::OnLBtnDown(int, int)
//    public void UIEditCtrl::OnDraw()
//    public void UIEditCtrl::OnBeginEdit()
//    public void UIEditCtrl::OnFinishEdit()
//    public void UIEditCtrl::SetText(const char *)
//    public unsigned char UIEditCtrl::CanGetFocus()
//    public int UIEditCtrl::SendMsg(class UIWindow *, int, int, int, int, int)
//    public void SetMaskChar(char)
//    public void SetTextLimit(int)
//    public void UIEditCtrl::SetFrameColor(int, int, int)
//    public void UIEditCtrl::SetTextColor(int, int, int)
//    public void UIEditCtrl::MakeSelect()
//    public void UIEditCtrl::DisableSelect(int)
//    public const char * UIEditCtrl::GetText()
//    public int UIEditCtrl::GetTextSize()
//    public void SetType(int)
//    protected void UIEditCtrl::DrawEditText()
//    protected void UIEditCtrl::RefreshText()
//    protected void UIEditCtrl::DrawSelectionBox(int, int)
//    protected void UIEditCtrl::UpdateKeyStroke(int)
//    protected void UIEditCtrl::UpdateCandidate(int)
//    protected void UIEditCtrl::SetTextByMaxChar()
//    /* this+0x48 */ int m_selectionOrigin
//    /* this+0x4c */ int m_selectionCursor
//    /* this+0x50 */ int m_maskchar
//    /* this+0x54 */ int m_maxchar
//    /* this+0x58 */ int m_isSingColorFrame
//    /* this+0x5c */ int m_r
//    /* this+0x60 */ int m_g
//    /* this+0x64 */ int m_b
//    /* this+0x68 */ int m_textR
//    /* this+0x6c */ int m_textG
//    /* this+0x70 */ int m_textB
//    /* this+0x74 */ int m_xOffset
//    /* this+0x78 */ int m_yOffset
//    /* this+0x7c */ int m_type
//    /* this+0x80 */ class std::string m_text
//
//    public class UIEditCtrl & operator=(const class UIEditCtrl &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UIEDITCTRL_H_
