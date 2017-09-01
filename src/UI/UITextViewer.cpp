#include "UITextViewer.h"

CUITextViewer::CUITextViewer() {
  m_curItem = 0;
  m_vertViewOffset = 0;
  m_horzViewOffset = 0;
  m_maxTextWidth = 0;
  m_vertScrollBar = 0;
  m_horzScrollBar = 0;
  m_vertScrEnabled = 0;
  m_horzScrEnabled = 0;
  m_isTransParent = 0;
  m_bR = 255;
  m_bG = 255;
  m_bB = 255;
  m_itemSpacing = 18;
  m_bgR = 0;  // TO CHANGE
  m_bgB = 0;
  m_bgG = 0;
  m_noColor = 0;
}

CUITextViewer::~CUITextViewer() {}

void CUITextViewer::OnCreate(int cx, int cy) { CUIListBox::OnCreate(cx, cy); }

void CUITextViewer::Create2(int x, int y, int cx, int cy, bool trans) {
  m_isTransParent = trans;
  Resize(cx, cy);
  Move(x, y);
  OnCreate(cx, cy);
  OnSize(cx, cy);
}

void CUITextViewer::OnDraw() {
  int h = 0;
  for (auto it = m_items.begin(); it != m_items.end(); ++it) {
    TextOutWithOutline(3, 4 + m_itemSpacing * h, it->c_str(), it->length(),
                       0, 0xFFFFFF, 0, 12, 0);
    h++;
  }
}