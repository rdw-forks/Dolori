#include "Language.h"

CLanguage::CLanguage() {
  m_selectionCursor = 0;
  m_selectionOrigin = 0;
  m_underLineStart = 0;
  m_underLineEnd = 0;
}

CLanguage::~CLanguage() {}

void CLanguage::AddInput(const char *input) { m_input += input; }

void CLanguage::ResetInput() { m_input.clear(); }

const char *CLanguage::GetLanguageText() { return m_input.c_str(); }