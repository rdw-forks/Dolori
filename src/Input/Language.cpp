#include "Input/Language.h"

CLanguage::CLanguage()
    : m_selectionCursor(),
      m_selectionOrigin(),
      m_underLineStart(),
      m_underLineEnd() {}

CLanguage::~CLanguage() {}

void CLanguage::AddInput(const char *input) { m_input += input; }

void CLanguage::ResetInput() { m_input.clear(); }

const char *CLanguage::GetLanguageText() { return m_input.c_str(); }
