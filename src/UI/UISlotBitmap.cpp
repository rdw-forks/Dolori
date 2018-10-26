#include "UI/UISlotBitmap.h"

CUISlotBitmap::CUISlotBitmap(CUIWindowMgr* p_window_mgr, size_t slot_id)
    : CUIStaticBitmap(p_window_mgr), m_slot_id(slot_id) {}

void CUISlotBitmap::OnLBtnDown(int x, int y) {
  if (m_parent) {
    m_parent->SendMsg(this, 13, reinterpret_cast<void*>(m_slot_id));
    m_parent->SendMsg(this, 6, reinterpret_cast<void*>(m_id));
  }
}

void* CUISlotBitmap::SendMsg(CUIWindow* sender, int message, void* val1,
                             void* val2, void* val3, void* val4) {
  if (message == 13) {
    size_t new_state = reinterpret_cast<size_t>(val1);

    if (m_state != new_state) {
      m_state = new_state;
      Invalidate();
    }

    return nullptr;
  }

  return CUIWindow::SendMsg(sender, message, val1, val2, val3, val4);
}
