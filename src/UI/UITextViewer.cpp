#include "UI/UITextViewer.h"

CUITextViewer::CUITextViewer(CUIWindowMgr* p_window_mgr)
    : CUIListBox(p_window_mgr), m_bgR(), m_bgB(), m_bgG() {
  m_itemSpacing = 18;
}

void CUITextViewer::OnCreate(int cx, int cy) { CUIListBox::OnCreate(cx, cy); }

void CUITextViewer::Create2(int x, int y, int cx, int cy, bool trans) {
  m_isTransParent = trans;
  Create(cx, cy);
  Move(x, y);
}

void CUITextViewer::OnDraw() {
  int spacing = m_itemSpacing - m_horzScrEnabled;
  size_t nb_of_items = m_items.size();
  size_t nb_of_items_shown;
  int div = 1;

  if (m_isTransParent) {
    ClearDC(0);
    if (m_parent) {
      m_parent->Invalidate();
    }
  } else {
    ClearDC((m_bgR << 16) | (m_bgG << 8) | m_bgB);
  }

  if (spacing) {
    div = spacing;
  }

  if (m_vertViewOffset + m_h / div >= nb_of_items) {
    nb_of_items_shown = nb_of_items;
  } else {
    nb_of_items_shown = m_vertViewOffset + m_h / div;
  }

  unsigned int color = 0;
  if (m_vertViewOffset > 0) {
    for (auto it = m_items.begin(); it != m_items.end(); ++it) {
      const char* str = it->c_str();
      size_t str_length = it->length();

      for (int i = 0; i < str_length; i++) {
        char* color_mark = 0;  // FindColorMark(str, str_length);
        str = InterpretColor(color_mark, &color);
      }
    }
  }

  if (m_noColor) {
    for (int i = 0; i < nb_of_items_shown; i++) {
      if (m_vertViewOffset + i >= nb_of_items) {
        break;
      }

      const std::string& str = m_items[m_vertViewOffset + i];
      size_t str_length = m_items[m_vertViewOffset + i].length();

      TextOutWithOutline(3, 4 + m_itemSpacing * (i - m_vertViewOffset), str,
                         str_length, 0, 0xFFFFFF, 0, 12, 0);
    }
  } else {
    for (int i = 0; i < nb_of_items_shown; i++) {
      if (m_vertViewOffset + i >= nb_of_items) {
        break;
      }

      const std::string& str = m_items[m_vertViewOffset + i];
      size_t str_length = m_items[m_vertViewOffset + i].length();

      TextOutWithDecoration(3, 4 + m_itemSpacing * (i - m_vertViewOffset), str,
                            str_length, &color, 0, 12);
    }
  }
}
