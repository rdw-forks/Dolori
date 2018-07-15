#include "UI/UIStaticBitmap.h"

#include "Common/Globals.h"
#include "UI/UIBmp.h"

CUIStaticBitmap::CUIStaticBitmap() {}

CUIStaticBitmap::~CUIStaticBitmap() { m_bitmap_name.clear(); }

void CUIStaticBitmap::SetBitmap(const char* filename) {
  CBitmapRes* res;

  m_bitmap_name = filename;
  res = (CBitmapRes*)g_ResMgr->Get(UIBmp(filename), false);
  m_w = res->GetWidth();
  m_h = res->GetHeight();
}

void CUIStaticBitmap::OnDraw() {
  if (m_bitmap_name.length()) {
    if (m_state == 1) {
      ClearDC(0);
    } else {
      CBitmapRes* res;
      res = (CBitmapRes*)g_ResMgr->Get(UIBmp(m_bitmap_name.c_str()), false);
      DrawBitmap(0, 0, res, 0);
    }
  }
}
