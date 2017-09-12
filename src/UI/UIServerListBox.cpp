#include "UIServerListBox.h"

CUIServerListBox::CUIServerListBox() {
  m_bR = 255;
  m_bG = 255;
  m_bB = 255;
  m_curItem = 0;
  m_vertViewOffset = 0;
  m_horzViewOffset = 0;
  m_maxTextWidth = 0;
  m_vertScrollBar = NULL;
  m_horzScrollBar = NULL;
  m_vertScrEnabled = 0;
  m_horzScrEnabled = 0;
  m_isTransParent = 0;
  m_itemSpacing = 16;
  m_serverBalloon = NULL;
}

CUIServerListBox::~CUIServerListBox() {}
