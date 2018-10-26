#ifndef DOLORI_UI_UISERVERLISTBOX_H_
#define DOLORI_UI_UISERVERLISTBOX_H_

#include <string>
#include <vector>

#include "UI/UIListBox.h"

class CUIServerListBox : public CUIListBox {
 public:
  CUIServerListBox(CUIWindowMgr* p_window_mgr);

 private:
  std::vector<std::string> m_strings;
  class UIBalloonText* m_serverBalloon;
};

// class UIServerListBox {
//  UIListBox, offset = 0x0
//
//    public void UIServerListBox(const class UIServerListBox &)
//    public void UIServerListBox::UIServerListBox()
//    public void UIServerListBox::~UIServerListBox()
//    public void UIServerListBox::OnMouseHover(int, int)
//    /* this+0x90 */ class std::vector<std::string, std::allocator<std::string
//    > > m_strings
//
//    /* this+0xa0 */ class UIBalloonText * m_serverBalloon
//    public class UIServerListBox & operator=(const class UIServerListBox &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UISERVERLISTBOX_H_
