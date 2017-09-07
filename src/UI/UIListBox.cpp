#include "UIListBox.h"

CUIListBox::CUIListBox() {}

CUIListBox::~CUIListBox() {}

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
}
