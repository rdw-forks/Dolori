#ifndef DOLORI_UI_UISELECTSERVERWND_H_
#define DOLORI_UI_UISELECTSERVERWND_H_

#include <string>

#include "UI/UIBitmapButton.h"
#include "UI/UIFrameWnd.h"
#include "UI/UIServerListBox.h"

class CUISelectServerWnd : public CUIFrameWnd {
 public:
  CUISelectServerWnd(CUIWindowMgr* p_window_mgr);

  void OnCreate(int cx, int cy) override;
  void OnDraw() override;
  void* SendMsg(CUIWindow* sender, int message, const void* val1 = nullptr,
                const void* val2 = nullptr, const void* val3 = nullptr,
                const void* val4 = nullptr) override;

  void AddServer(const char* server);

 private:
  CUIServerListBox* m_serverList;
  CUIBitmapButton* m_exitButton;
  std::string m_regKey;
  int m_defaultCurItem;
  size_t m_target;
};

// class UISelectServerWnd {
//  UIFrameWnd, offset = 0x0
//
//    public void UISelectServerWnd(const class UISelectServerWnd &)
//    public void UISelectServerWnd::UISelectServerWnd()
//    public void UISelectServerWnd::~UISelectServerWnd()
//    public void UISelectServerWnd::OnCreate(int, int)
//    public void UISelectServerWnd::OnDraw()
//    public int UISelectServerWnd::SendMsg(class UIWindow *, int, int, int,
//    int, int) public void UISelectServerWnd::OnDestroy() public void
//    UISelectServerWnd::InitDefaultCurItemFromReg(const char *) public void
//    UISelectServerWnd::SaveCurItemToReg(const char *)
//    /* this+0x60 */ class UIServerListBox * m_serverList
//    /* this+0x64 */ class UIBitmapButton * m_exitButton
//    /* this+0x68 */ class std::string m_regKey
//
//    /* this+0x78 */ int m_defaultCurItem
//    /* this+0x7c */ int m_target
//    public class UISelectServerWnd & operator=(const class UISelectServerWnd
//    &) public void __local_vftable_ctor_closure() public void *
//    __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UISELECTSERVERWND_H_
