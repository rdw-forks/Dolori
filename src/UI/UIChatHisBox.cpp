#include "UI/UIChatHisBox.h"

CUIChatHisBox::CUIChatHisBox(CUIWindowMgr* p_window_mgr)
    : CUIListBox(p_window_mgr),
      talker_names_(),
      item_colors_(),
      max_items_(240) {
  m_itemSpacing = 14;
}

void CUIChatHisBox::OnCreate(int x, int y) { CUIListBox::OnCreate(x, y); }

void CUIChatHisBox::OnDraw() {
  const size_t nb_of_items = m_items.size();
  size_t nb_of_items_shown;
  uint32_t color = 0;
  int div = 1;

  ClearDC(0x50FFFFFF);

  if (m_parent != nullptr && m_x >= 0 && m_y >= 0) {
    m_parent->OnDraw();
  }

  if (m_itemSpacing != 0) {
    div = m_itemSpacing;
  }

  if (m_vertViewOffset + m_h / div >= nb_of_items) {
    nb_of_items_shown = nb_of_items;
  } else {
    nb_of_items_shown = m_vertViewOffset + m_h / div;
  }

  for (int i = 0; i < nb_of_items_shown; i++) {
    if (m_vertViewOffset + i >= nb_of_items) {
      break;
    }

    if (m_vertViewOffset + i < 0) {
      continue;
    }

    const auto& item = m_items[m_vertViewOffset + i];
    TextOutUTF8(3, i * m_itemSpacing + 4, item, 0, 0, 12, 0);
    TextOutUTF8(2, i * m_itemSpacing + 3, item, 0, 0, 12,
                item_colors_[m_vertViewOffset + i]);
  }
}

void CUIChatHisBox::AddItem(const std::string& message, uint32_t color) {
  const size_t nb_of_visible_lines = m_h / m_itemSpacing;
  bool is_bottom_line = false;

  if (!m_vertScrEnabled ||
      m_vertViewOffset + nb_of_visible_lines == m_items.size()) {
    is_bottom_line = true;
  }

  CUIListBox::AddItem(message);
  item_colors_.push_back(color);

  // Automatically scroll down if we're already at the bottom of the list
  if (m_vertScrEnabled && !m_horzScrEnabled && is_bottom_line) {
    m_vertViewOffset = m_items.size() - nb_of_visible_lines;
    m_vertScrollBar->SetPos(m_vertViewOffset);
    m_vertScrollBar->Invalidate();
  }

  Invalidate();
}
