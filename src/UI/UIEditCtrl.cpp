#include "UI/UIEditCtrl.h"

#include "Common/Globals.h"
#include "Common/const_strings.h"
#include "UI/UIBmp.h"

CUIEditCtrl::CUIEditCtrl(CUIWindowMgr* p_window_mgr)
    : CUIWindow(p_window_mgr),
      m_selectionOrigin(0),
      m_selectionCursor(0),
      m_maskchar(false),
      m_maxchar(255),
      m_isSingColorFrame(1),
      m_r(255),
      m_g(255),
      m_b(255),
      m_text_color(0),
      m_xOffset(0),
      m_yOffset(0),
      m_type(0) {}

void CUIEditCtrl::HideChars(bool hide_chars) {
  m_maskchar = hide_chars;
  g_Language->HideText(m_maskchar);
}

void CUIEditCtrl::SetFrameColor(int r, int g, int b) {
  m_r = r;
  m_g = g;
  m_b = b;
  Invalidate();
}

void CUIEditCtrl::OnLBtnDown(int x, int y) {
  p_window_mgr_->SetFocusEdit(this);
}

void CUIEditCtrl::OnDraw() {
  if (m_isSingColorFrame) {
    ClearDC((0xFF << 24) | (m_b << 16) | (m_g << 8) | m_r);
    m_yOffset = 2;
    DrawEditText();
    return;
  }

  const std::string dialog_l_name =
      const_strings::kResourceSubfolder + "type_dialog_l.bmp";
  const std::string dialog_m_name =
      const_strings::kResourceSubfolder + "type_dialog_m.bmp";
  const std::string dialog_r_name =
      const_strings::kResourceSubfolder + "type_dialog_r.bmp";
  CBitmapRes* bitmap;

  bitmap = static_cast<CBitmapRes*>(g_ResMgr->Get(UIBmp(dialog_l_name), false));
  DrawBitmap(0, 0, bitmap, 0);

  const int nb_of_elements = (m_w - 20) / 24;
  int pos_x = 10;
  if (nb_of_elements > 0) {
    bitmap =
        static_cast<CBitmapRes*>(g_ResMgr->Get(UIBmp(dialog_m_name), false));
    for (int i = 0; i < nb_of_elements; i++) {
      DrawBitmap(pos_x, 0, bitmap, 0);
      pos_x += 24;
    }
  }

  bitmap = static_cast<CBitmapRes*>(g_ResMgr->Get(UIBmp(dialog_r_name), false));
  DrawBitmap(24 * pos_x + 10, 0, bitmap, 0);
  m_yOffset = 5;
  DrawEditText();
}

void CUIEditCtrl::DrawEditText() {
  if (p_window_mgr_->GetFocusEdit() == this) {
    RefreshText();
  }

  TextOutUTF8(m_xOffset, m_yOffset, m_text, 0, 0, 12, m_text_color);
}

void CUIEditCtrl::OnBeginEdit() {
  g_Language->ResetInput();
  g_Language->HideText(m_maskchar);
  g_Language->AddInput(m_text);
  if (p_window_mgr_->GetFocusEdit() == this) {
    g_Language->SetSelection(0, g_Language->GetInputSize());
  } else {
    m_selectionOrigin = 0;
    m_selectionCursor = m_text.length();
  }

  SDL_StartTextInput();
}

void CUIEditCtrl::OnFinishEdit() {
  SDL_StopTextInput();
  RefreshText();
  Invalidate();
}

void CUIEditCtrl::RefreshText() { m_text = g_Language->GetLanguageText(); }

void CUIEditCtrl::SetText(std::string text) {
  m_text = std::move(text);

  if (p_window_mgr_->GetFocusEdit() == this) {
    g_Language->ResetInput();
    g_Language->AddInput(m_text);
    g_Language->SetSelection(0, g_Language->GetInputSize());
  }

  Invalidate();
}

const std::string& CUIEditCtrl::GetText() {
  if (p_window_mgr_->GetFocusEdit() == this) {
    RefreshText();
  }

  return m_text;
}

size_t CUIEditCtrl::GetTextSize() const { return m_text.length(); }

void CUIEditCtrl::SetTextLimit(size_t max) { m_maxchar = max; }
