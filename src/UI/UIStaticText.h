#ifndef DOLORI_UI_UISTATICTEXT_H_
#define DOLORI_UI_UISTATICTEXT_H_

#include <string>

#include "UI/UIWindow.h"

class CUIStaticText : public CUIWindow {
 public:
  CUIStaticText();
  ~CUIStaticText();

  void OnDraw() override;
  void SetText(const std::string& text, int drawBold);

 private:
  int m_drawBackGround;
  int m_backR;
  int m_backG;
  int m_backB;
  int m_textR;
  int m_textG;
  int m_textB;
  int m_drawTwice;
  int m_drawBold;
  int m_fontHeight;
  int m_fontType;
  int m_isShorten;
  std::string m_text;
  std::string m_fullText;
};

// class UIStaticText {
//  UIWindow,
//      offset =
//          0x0
//
//              public void
//              UIStaticText(const class UIStaticText &) public void
//              UIStaticText::UIStaticText() public void
//                  UIStaticText::~UIStaticText() public void
//                  UIStaticText::OnDraw() public void
//                  UIStaticText::OnLBtnDown(int, int) public void
//                  UIStaticText::OnLBtnDblClk(int, int) public void
//                  UIStaticText::OnMouseMove(int, int) public void
//                  UIStaticText::OnLBtnUp(int, int) public void
//                  UIStaticText::OnMouseHover(int, int) public void
//                  UIStaticText::OnMouseShape(int, int) public void
//                  UIStaticText::OnWheel(int) public void
//                  UIStaticText::OnRBtnDown(int, int) public void
//                  UIStaticText::OnRBtnUp(int, int) public void
//                  UIStaticText::SetText(const char *, int) public void
//                  UIStaticText::SetTextWithNumber(int) public void
//                  UIStaticText::SetTextWithShorten(const char *) public void
//                  UIStaticText::SetTextWithNewWidth(const char *) public void
//                  UIStaticText::SetFont(int, int) public void
//                  UIStaticText::SetTextColor(int, int, int) public const char
//                  *
//              GetFullText()
//              /* this+0x48 */ int m_drawBackGround
//              /* this+0x4c */ int m_backR
//              /* this+0x50 */ int m_backG
//              /* this+0x54 */ int m_backB
//              /* this+0x58 */ int m_textR
//              /* this+0x5c */ int m_textG
//              /* this+0x60 */ int m_textB
//              /* this+0x64 */ int m_drawTwice
//              /* this+0x68 */ int m_drawBold
//              /* this+0x6c */ int m_fontHeight
//              /* this+0x70 */ int m_fontType
//              /* this+0x74 */ int m_isShorten
//              /* this+0x78 */ class std::string m_text
//
//              /* this+0x88 */ class std::string m_fullText
//
//              public class UIStaticText &
//          operator=(const class UIStaticText &) public void
//              __local_vftable_ctor_closure() public void *
//              __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UISTATICTEXT_H_
