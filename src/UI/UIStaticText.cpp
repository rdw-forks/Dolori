#include "UI/UIStaticText.h"

CUIStaticText::CUIStaticText()
    : m_drawBackGround(),
      m_backR(255),
      m_backG(255),
      m_backB(255),
      m_textR(),
      m_textG(),
      m_textB(),
      m_drawTwice(),
      m_drawBold(),
      m_fontHeight(12),
      m_fontType(),
      m_isShorten() {}

CUIStaticText::~CUIStaticText() {}

void CUIStaticText::OnDraw() {
  uint32_t color = (m_textR << 16) | (m_textG << 8) | m_textB;

  if (m_drawBackGround) {
    ClearDC((0xFF << 24) | (m_backR << 16) | (m_backG << 8) | m_backR);
  } else {
    ClearDC(0);
  }

  if (m_drawTwice) {
  }

  if (m_drawBold) {
  }

  TextOutA(0, 0, m_text.c_str(), 0, m_fontType, m_fontHeight, color);
}

void CUIStaticText::SetText(const char *txt, int drawBold) {
  m_drawBold = drawBold;
  m_text = txt;
  m_fullText = txt;
  m_isShorten = false;
  Invalidate();
}
