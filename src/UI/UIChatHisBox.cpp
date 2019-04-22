#include "UIChatHisBox.h"
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
  CUIListBox::AddItem(message);
  item_colors_.push_back(color);
}
