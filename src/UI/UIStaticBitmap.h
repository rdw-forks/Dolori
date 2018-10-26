#ifndef DOLORI_UI_UISTATICBITMAP_H_
#define DOLORI_UI_UISTATICBITMAP_H_

#include <string>

#include "UI/UIWindow.h"

class CUIStaticBitmap : public CUIWindow {
 public:
  CUIStaticBitmap(CUIWindowMgr* p_window_mgr);
  ~CUIStaticBitmap();

  void SetBitmap(const char* filename);
  void OnDraw();

 private:
  std::string m_bitmap_name;
};

// class UIStaticBitmap {
//  UIWindow, offset = 0x0
//
//    public void UIStaticBitmap(const class UIStaticBitmap &)
//    public void UIStaticBitmap::UIStaticBitmap()
//    public void UIStaticBitmap::~UIStaticBitmap()
//    public void UIStaticBitmap::OnLBtnDown(int, int)
//    public void UIStaticBitmap::OnMouseMove(int, int)
//    public void UIStaticBitmap::OnLBtnUp(int, int)
//    public void UIStaticBitmap::OnDraw()
//    public void UIStaticBitmap::SetBitmap(const char *)
//    /* this+0x48 */ class std::string m_bitmapName
//
//    public class UIStaticBitmap & operator=(const class UIStaticBitmap &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UISTATICBITMAP_H_
