#ifndef DOLORI_UI_UIBITMAPEDITCTRL_H_
#define DOLORI_UI_UIBITMAPEDITCTRL_H_

#include <string>

#include "UI/UIEditCtrl.h"

class CUIBitmapEditCtrl : public CUIEditCtrl {
 public:
  CUIBitmapEditCtrl();

  void OnDraw() override;

  void SetBitmap(const std::string& bitmap_name);

 private:
  std::string m_bitmapName;
};

// class UIBitmapEditCtrl {
//	UIEditCtrl, offset = 0x0
//
//		public void UIBitmapEditCtrl::OnDraw()
//		public void UIBitmapEditCtrl::SetBitmap(const char *)
//		/* this+0x90 */ class std::string m_bitmapName
//
//		public void UIBitmapEditCtrl(const class UIBitmapEditCtrl &)
//		public void UIBitmapEditCtrl()
//		public class UIBitmapEditCtrl & operator=(const class
// UIBitmapEditCtrl &) 		public void
// UIBitmapEditCtrl::~UIBitmapEditCtrl() 		public void
// __local_vftable_ctor_closure() 		public void *
// __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UIBITMAPEDITCTRL_H_
