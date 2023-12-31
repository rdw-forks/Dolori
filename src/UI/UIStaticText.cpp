#include "UI/UIStaticText.h"

CUIStaticText::CUIStaticText(CUIWindowMgr* p_window_mgr)
    : CUIWindow(p_window_mgr),
      m_drawBackGround(),
      m_backR(255),
      m_backG(255),
      m_backB(255),
      m_textR(0),
      m_textG(0),
      m_textB(0),
      m_drawTwice(false),
      m_drawBold(false),
      m_fontHeight(12),
      m_fontType(),
      m_isShorten() {}

void CUIStaticText::OnDraw() {
  const uint32_t color = (m_textR << 16) | (m_textG << 8) | m_textB;

  if (m_drawBackGround) {
    ClearDC((0xFF << 24) | (m_backR << 16) | (m_backG << 8) | m_backR);
  } else {
    ClearDC(0);
  }

  if (m_drawTwice) {
  }

  if (m_drawBold) {
  }

  TextOutA(0, 0, m_text, 0, m_fontType, m_fontHeight, color);
}

void CUIStaticText::SetText(const std::string& text, bool drawBold) {
  m_drawBold = drawBold;
  m_text = text;
  m_fullText = text;
  m_isShorten = false;
  Invalidate();
}
