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
  ClearDC(0xFFFF00FF);

  if (m_parent != nullptr && m_x >= 0 && m_y >= 0) {
    // m_parent->OnDraw2();
  }

  int y = m_vertViewOffset;
  for (const auto& item : m_items) {
    TextOutUTF8(3, y * m_itemSpacing + 4, item.c_str(), 0, 0, 12, 0);
    y++;
  }
}
