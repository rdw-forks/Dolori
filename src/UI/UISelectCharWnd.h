#ifndef DOLORI_UI_UISELECTCHARWND_H_
#define DOLORI_UI_UISELECTCHARWND_H_

#include "../Render/view_sprite.h"
#include "UIBitmapButton.h"
#include "UIFrameWnd.h"
#include "UISlotBitmap.h"
#include "UIStaticText.h"

#define NB_OF_SLOTS 12
#define SLOTS_PER_PAGE 3

class CUISelectCharWnd : public CUIFrameWnd {
 public:
  CUISelectCharWnd();
  ~CUISelectCharWnd();

  void OnCreate(int cx, int cy);
  void OnLBtnDown(int x, int y);
  void OnDraw();
  void InitTextControls();
  void* SendMsg(CUIWindow* sender, int message, void* val1, void* val2,
                void* val3, void* val4);
  void MakeButton(int id);

 private:
  struct VIEW_SPRITE m_viewChar[NB_OF_SLOTS];
  bool m_isEmpty[NB_OF_SLOTS];
  bool m_isAvailable[NB_OF_SLOTS];
  short m_accessory_top[NB_OF_SLOTS];
  unsigned long m_stateStartTick;
  bool m_dontmove;
  int m_cur_page;
  int m_cur_slot;
  int m_pageCount;
  CUIBitmapButton* m_ok_button;
  CUIBitmapButton* m_make_button;
  CUIBitmapButton* m_cancel_button;
  CUIBitmapButton* m_delete_button;
  CUIBitmapButton* m_notice_button;
  CUIBitmapButton* m_charge_button;
  CUIStaticText* m_text[NB_OF_SLOTS];
  CUISlotBitmap* m_slots[NB_OF_SLOTS + 1];
  CUIBitmapButton* m_change_name_btn;
};

// class UISelectCharWnd {
//  UIFrameWnd, offset = 0x0
//
//    public void UISelectCharWnd(const class UISelectCharWnd &)
//    public void UISelectCharWnd::UISelectCharWnd()
//    public void UISelectCharWnd::~UISelectCharWnd()
//    public void UISelectCharWnd::OnCreate(int, int)
//    public void UISelectCharWnd::OnProcess()
//    public void UISelectCharWnd::OnMouseMove(int, int)
//    public void UISelectCharWnd::OnLBtnDown(int, int)
//    public void UISelectCharWnd::OnDraw()
//    public int UISelectCharWnd::SendMsg(class UIWindow *, int, int, int, int,
//    int) public void UISelectCharWnd::InvalidateWallPaper() public void
//    UISelectCharWnd::MakeButton(int) public void
//    UISelectCharWnd::DeleteButton(int) public void
//    UISelectCharWnd::WriteToReg() public void
//    UISelectCharWnd::InitTextControls() public void
//    UISelectCharWnd::InitFromReg()
//    /* this+0x60 */ struct viewSprite[0xc] m_viewChar
//    /* this+0xb70 */ int[0xc] m_isEmpty
//    /* this+0xba0 */ unsigned char[0xc] m_isAvailable
//    /* this+0xbac */ short[0xc] m_accessory_top
//    /* this+0xbc4 */ unsigned long m_stateStartTick
//    /* this+0xbc8 */ char m_dontmove
//    /* this+0xbcc */ int m_curPage
//    /* this+0xbd0 */ int m_curSlot
//    /* this+0xbd4 */ int m_pageCount
//    /* this+0xbd8 */ class UIBitmapButton * m_okButton
//    /* this+0xbdc */ class UIBitmapButton * m_makeButton
//    /* this+0xbe0 */ class UIBitmapButton * m_cancelButton
//    /* this+0xbe4 */ class UIBitmapButton * m_deleteButton
//    /* this+0xbe8 */ class UIBitmapButton * m_noticeButton
//    /* this+0xbec */ class UIBitmapButton * m_chargeButton
//    /* this+0xbf0 */ class UIStaticText *[0x16] m_text
//    /* this+0xc48 */ class UISlotBitmap *[0xd] m_slots
//    /* this+0xc7c */ class UIBitmapButton * m_changeNameBtn
//    public class UISelectCharWnd & operator=(const class UISelectCharWnd &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UISELECTCHARWND_H_
