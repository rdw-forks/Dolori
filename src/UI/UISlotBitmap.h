#ifndef DOLORI_UI_UISLOTBITMAP_H_
#define DOLORI_UI_UISLOTBITMAP_H_

#include "UIStaticBitmap.h"

class CUISlotBitmap : public CUIStaticBitmap {
 public:
  CUISlotBitmap(int slot_id);
  ~CUISlotBitmap();

  void OnLBtnDown(int x, int y);
  void* SendMsg(CUIWindow* sender, int message, void* val1, void* val2,
                void* val3, void* val4);

 private:
  int m_slot_id;
};

// class UISlotBitmap {
//  UIStaticBitmap, offset = 0x0
//
//    public void UISlotBitmap(const class UISlotBitmap &)
//    public void UISlotBitmap::UISlotBitmap(int)
//    public void UISlotBitmap::~UISlotBitmap()
//    public void UISlotBitmap::OnLBtnDown(int, int)
//    public void UISlotBitmap::OnLBtnDblClk(int, int)
//    public int UISlotBitmap::SendMsg(class UIWindow *, int, int, int, int,
//    int)
//    /* this+0x58 */ int m_nSlotID
//    public class UISlotBitmap & operator=(const class UISlotBitmap &)
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UISLOTBITMAP_H_