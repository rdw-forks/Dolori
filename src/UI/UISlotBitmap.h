#ifndef DOLORI_UI_UISLOTBITMAP_H_
#define DOLORI_UI_UISLOTBITMAP_H_

#include "UI/UIStaticBitmap.h"

class CUISlotBitmap : public CUIStaticBitmap {
 public:
  CUISlotBitmap(CUIWindowMgr* p_window_mgr, size_t slot_id);

  void OnLBtnDown(int x, int y);
  void* SendMsg(CUIWindow* sender, int message, void* val1 = nullptr,
                void* val2 = nullptr, void* val3 = nullptr,
                void* val4 = nullptr);

 private:
  size_t m_slot_id;
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
