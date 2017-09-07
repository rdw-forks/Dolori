#include "UIStaticText.h"

CUIStaticText::CUIStaticText() {}

CUIStaticText::~CUIStaticText() {}

void CUIStaticText::OnDraw() {
  uint32_t color = (m_textR << 16) | (m_textG << 8) | m_textB;

  if (m_drawBackGround) {
  }

  if (m_drawTwice) {
  }

  if (m_drawBold) {
  }

  TextOutA(0, 0, m_text.c_str(), 0, m_fontType, m_fontHeight, color);
}
