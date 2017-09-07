#include "UIEditCtrl.h"
#include "../Common/Globals.h"
#include "UIBmp.h"

CUIEditCtrl::CUIEditCtrl() {
  m_maxchar = 255;
  m_selectionCursor = 0;
  m_selectionOrigin = 0;
  m_maskchar = 0;
  m_isSingColorFrame = 1;
  m_r = 255;
  m_g = 255;
  m_b = 255;
  m_textR = 0;
  m_textG = 0;
  m_textB = 0;
  m_xOffset = 0;
  m_yOffset = 0;
  m_type = 0;
}

CUIEditCtrl::~CUIEditCtrl() {}

void CUIEditCtrl::SetFrameColor(int r, int g, int b) {
  m_r = r;
  m_g = g;
  m_b = b;
  Invalidate();
}

void CUIEditCtrl::OnLBtnDown(int x, int y) { g_WindowMgr->SetFocusEdit(this); }

void CUIEditCtrl::OnDraw() {
  if (m_isSingColorFrame) {
    ClearDC((m_r << 16) | (m_g << 8) | m_b);
    m_yOffset = 2;
  } else {
    CBitmapRes* bitmap;

    bitmap = (CBitmapRes*)g_ResMgr->Get(
        UIBmp("유저인터페이스/type_dialog_l.bmp"), false);
    DrawBitmap(0, 0, bitmap, 0);

    int nb_of_elements = (m_w - 20) / 24;
    int pos_x = 10;
    if (nb_of_elements > 0) {
      bitmap = (CBitmapRes*)g_ResMgr->Get(
          UIBmp("유저인터페이스/type_dialog_m.bmp"), false);
      for (int i = 0; i < nb_of_elements; i++) {
        DrawBitmap(pos_x, 0, bitmap, 0);
        pos_x += 24;
      }
    }

    bitmap = (CBitmapRes*)g_ResMgr->Get(
        UIBmp("유저인터페이스/type_dialog_r.bmp"), false);
    DrawBitmap(24 * pos_x + 10, 0, bitmap, 0);

    m_yOffset = 5;
  }
}
