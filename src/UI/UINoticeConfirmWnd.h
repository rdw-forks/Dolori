#ifndef DOLORI_UI_UINOTICECONFIRMWND_H_
#define DOLORI_UI_UINOTICECONFIRMWND_H_

#include "UI/UIFrameWnd.h"
#include "UI/UITextViewer.h"

class CUINoticeConfirmWnd : public CUIFrameWnd {
 public:
  CUINoticeConfirmWnd(CUIWindowMgr *p_window_mgr);

  void OnCreate(int cx, int cy) override;
  void OnDraw() override;
  void *SendMsg(CUIWindow *, int, const void *val1 = nullptr,
                const void *val2 = nullptr, const void *val3 = nullptr,
                const void *val4 = nullptr) override;

 private:
  CUITextViewer *m_textViewer;
  size_t m_target;
};

// class UINoticeConfirmWnd {
//  UIFrameWnd, offset = 0x0
//
//    public void UINoticeConfirmWnd(const class UINoticeConfirmWnd &)
//    public void UINoticeConfirmWnd::UINoticeConfirmWnd()
//    public void UINoticeConfirmWnd::~UINoticeConfirmWnd()
//    public void UINoticeConfirmWnd::OnCreate(int, int)
//    public void UINoticeConfirmWnd::OnDraw()
//    public int UINoticeConfirmWnd::SendMsg(class UIWindow *, int, int, int,
//    int, int)
//    /* this+0x60 */ class UITextViewer * m_textViewer
//    /* this+0x64 */ int m_target
//    public class UINoticeConfirmWnd & operator=(const class UINoticeConfirmWnd
//    &) public void __local_vftable_ctor_closure() public void *
//    __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UINOTICECONFIRMWND_H_
