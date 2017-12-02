#ifndef DOLORI_UI_UILOGINWND_H_
#define DOLORI_UI_UILOGINWND_H_

#include <string>
#include <vector>
#include "UIBitmapButton.h"
#include "UIEditCtrl.h"
#include "UIFrameWnd.h"
#include "UIStaticText.h"

class CUILoginWnd : public CUIFrameWnd {
 public:
  CUILoginWnd();
  ~CUILoginWnd();

  void OnCreate(int x, int y);
  void OnDraw();
  void* SendMsg(CUIWindow* sender, int message, void* val1, void* val2,
                void* val3, void* val4);

 private:
  CUIEditCtrl* m_login;
  CUIEditCtrl* m_password;
  CUIBitmapButton* m_cancel_button;
  int m_isCheckOn;
  int m_isGravity;
  int m_isHangame;
  CUIStaticText* m_classText;
  std::vector<std::string> m_classStringList;
  int m_comboMode;
};

// class UILoginWnd {
//  UIFrameWnd, offset = 0x0
//
//    public void UILoginWnd(const class UILoginWnd &)
//    public void UILoginWnd::UILoginWnd()
//    public void UILoginWnd::~UILoginWnd()
//    public void UILoginWnd::OnCreate(int, int)
//    public void UILoginWnd::OnDraw()
//    public void UILoginWnd::OnDestroy()
//    public void UILoginWnd::StoreInfo()
//    public int UILoginWnd::SendMsg(class UIWindow *, int, int, int, int, int)
//    public void UILoginWnd::InitFromReg()
//    public void UILoginWnd::WriteToReg()
//    public void UILoginWnd::OpenRegistPage()
//    /* this+0x60 */ class UIEditCtrl * m_login
//    /* this+0x64 */ class UIEditCtrl * m_password
//    /* this+0x68 */ class UIBitmapButton * m_cancelButton
//    /* this+0x6c */ int m_isCheckOn
//    /* this+0x70 */ int m_isGravity
//    /* this+0x74 */ int m_isHangame
//    /* this+0x78 */ class UIStaticText * m_classText
//    /* this+0x7c */ class std::vector<std::string, std::allocator<std::string
//    > > m_classStringList
//
//    /* this+0x8c */ int m_comboMode
//    public class UILoginWnd & operator=(const class UILoginWnd &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UILOGINWND_H_