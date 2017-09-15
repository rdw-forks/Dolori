#include "UIListBox.h"

CUIListBox::CUIListBox() {
  m_curItem = 0;
  m_vertViewOffset = 0;
  m_horzViewOffset = 0;
  m_maxTextWidth = 0;
  m_vertScrollBar = 0;
  m_horzScrollBar = 0;
  m_vertScrEnabled = 0;
  m_horzScrEnabled = 0;
  m_isTransParent = false;
  SetColor(255, 255, 255);
  m_itemSpacing = 16;
}

CUIListBox::~CUIListBox() {}

void CUIListBox::Create2(int x, int y, int cx, int cy, bool trans) {
  m_isTransParent = trans;
  Create(cx, cy);
  Move(x, y);
}

void CUIListBox::SetColor(int r, int g, int b) {
  m_bR = r;
  m_bG = g;
  m_bB = b;
}

void CUIListBox::Resize(int cx, int cy) {
  CUIWindow::Resize(cx, cy);
  if (m_vertScrollBar) {
    m_vertScrollBar->Resize(12, cy);
    m_vertScrollBar->Move(cx - 13, 0);
  }
  if (m_horzScrollBar) {
    m_horzScrollBar->Resize(cx - 13, 12);
    m_horzScrollBar->Move(0, cy - 13);
  }
  RecalcScrbarPos();
}

void CUIListBox::RecalcScrbarPos() {
  size_t nb_of_items_shown = m_h / m_itemSpacing;
  size_t nb_of_items = m_items.size();

  if (nb_of_items <= nb_of_items_shown)
    m_vertScrEnabled = 0;
  else
    m_vertScrEnabled = 1;

  if (m_vertScrEnabled) {
    m_vertScrollBar->SetRange(
        m_horzScrEnabled + nb_of_items - nb_of_items_shown, nb_of_items_shown,
        nb_of_items);
  } else {
  }
}

int CUIListBox::GetSelected() { return m_curItem; }

void CUIListBox::OnCreate(int cx, int cy) {
  int fixed_length;

  m_vertScrollBar = new CUIScrollBar();
  m_vertScrollBar->SetVert(true);
  fixed_length = m_vertScrollBar->GetFixedLength();
  m_vertScrollBar->Resize(fixed_length, cy);
  m_vertScrollBar->Move(cx - 13, 0);
  m_vertScrollBar->OnCreate(fixed_length, cy);
  m_vertScrollBar->OnSize(fixed_length, cy);
  AddChild(m_vertScrollBar);

  m_horzScrollBar = new CUIScrollBar();
  m_horzScrollBar->SetVert(false);
  fixed_length = m_horzScrollBar->GetFixedLength();
  m_horzScrollBar->Resize(cx - 13, fixed_length);
  m_horzScrollBar->Move(0, cy - 13);
  m_horzScrollBar->OnCreate(cx - 13, fixed_length);
  m_horzScrollBar->OnSize(cx - 13, fixed_length);
  AddChild(m_horzScrollBar);
}

void CUIListBox::AddItem(const char *txt) {
  m_items.push_back(txt);
  RecalcScrbarPos();
}

void CUIListBox::OnDraw() {
  int spacing = m_itemSpacing - m_horzScrEnabled;
  size_t nb_of_items = m_items.size();
  size_t nb_of_items_shown;
  uint32_t color = 0;
  int div = 1;

  if (m_isTransParent) {
    ClearDC(0);
    if (m_parent) m_parent->Invalidate();
  } else {
    ClearDC((m_bR << 16) | (m_bG << 8) | m_bB);
  }

  if (spacing) div = spacing;
  if (m_vertViewOffset + m_h / div >= nb_of_items)
    nb_of_items_shown = nb_of_items;
  else
    nb_of_items_shown = m_vertViewOffset + m_h / div;

  const char *str;
  size_t str_length;
  for (int i = 0; i < nb_of_items_shown; i++) {
    if (m_vertViewOffset + i >= nb_of_items) break;
    if (m_vertViewOffset + i == m_curItem)
      DrawBox(0, m_itemSpacing * i, m_w, m_itemSpacing - 1, 0xFFFBDFCA);

    str = m_items[m_vertViewOffset + i].c_str();
    str_length = m_items[m_vertViewOffset + i].length();
    TextOutWithDecoration(3 - m_horzViewOffset, m_itemSpacing * i, str,
                          str_length, &color, 0, 12);
  }
}

void CUIListBox::OnLBtnDown(int x, int y) {
  int target_id = m_vertViewOffset + y / m_itemSpacing;

  if (x < 0 || y < 0 || x >= m_w || y >= m_h || target_id < 0 ||
      target_id >= m_items.size())
    m_curItem = -1;
  else
    m_curItem = target_id;

  Invalidate();
}

int CUIListBox::SendMsg(CUIWindow *sender, int message, int val1, int val2,
                        int val3, int val4) {
  int prev_view_offset;
  int nb_of_items;

  switch (message) {
    case 7:
    case 9:
    case 10:
      prev_view_offset = m_vertViewOffset;
      if (message == 9)
        m_vertViewOffset -= m_h / m_itemSpacing - 1;
      else if (message == 10)
        m_vertViewOffset += m_h / m_itemSpacing - 1;
      else
        m_vertViewOffset += val1;

      if (m_vertViewOffset < 0) m_vertViewOffset = 0;
      nb_of_items = m_items.size();
      if (m_vertViewOffset >
          (m_horzScrEnabled - m_h / m_itemSpacing) + nb_of_items) {
        m_vertViewOffset =
            nb_of_items + (m_horzScrEnabled - m_h / m_itemSpacing);
      }

      m_vertScrollBar->SetPos(m_vertViewOffset);
      m_vertScrollBar->Invalidate();
      Invalidate();
      if (m_isTransParent && m_parent) m_parent->Invalidate();

      return m_vertViewOffset - prev_view_offset;
  };

  return 0;
}

int CUIListBox::HitTest(int x, int y) {
  int target_id = m_vertViewOffset + y / m_itemSpacing;
  int result;

  if (x < 0 || y < 0 || x >= m_w || y >= m_h || target_id < 0 ||
      target_id >= m_items.size())
    result = -1;
  else
    result = target_id;

  return result;
}