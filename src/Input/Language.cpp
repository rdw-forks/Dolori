#include "Input/Language.h"

CLanguage::CLanguage()
    : m_selectionCursor(),
      m_selectionOrigin(),
      m_bHideText(),
      m_underLineStart(),
      m_underLineEnd() {}

CLanguage::~CLanguage() {}

void CLanguage::AddInput(const std::string &input) { m_input += input; }

void CLanguage::ResetInput() { m_input.clear(); }

int CLanguage::GetInputSize() const { return m_input.length(); }

void CLanguage::SetSelection(int cursor_pos, int selection_len) {
  m_selectionOrigin = cursor_pos;
  m_selectionCursor = cursor_pos + selection_len;
}

std::string CLanguage::GetLanguageText() const {
  if (m_bHideText) {
    return std::string(m_input.length(), '*');
  }

  return m_input;
}

void CLanguage::HideText(bool hide_text) { m_bHideText = hide_text; }

void CLanguage::OnKeyDown(unsigned int, long) {}
