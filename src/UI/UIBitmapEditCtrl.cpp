#include "UI/UIBitmapEditCtrl.h"

#include "Common/Globals.h"
#include "UI/UIBmp.h"

CUIBitmapEditCtrl::CUIBitmapEditCtrl(CUIWindowMgr* p_window_mgr)
    : CUIEditCtrl(p_window_mgr), m_bitmapName() {}

void CUIBitmapEditCtrl::SetBitmap(const std::string& bitmap_name) {
  m_bitmapName = bitmap_name;

  auto bitmap =
      static_cast<CBitmapRes*>(g_ResMgr->Get(UIBmp(m_bitmapName), false));

  m_w = bitmap->GetWidth();
  m_h = bitmap->GetHeight();
}

void CUIBitmapEditCtrl::OnDraw() {
  ClearDC(0xFFFFFFFF);

  auto bitmap =
      static_cast<CBitmapRes*>(g_ResMgr->Get(UIBmp(m_bitmapName), false));
  DrawBitmap(0, 0, bitmap, 0);

  m_yOffset = 3;
  CUIEditCtrl::DrawEditText();
}
