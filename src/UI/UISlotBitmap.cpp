#include "UISlotBitmap.h"

CUISlotBitmap::CUISlotBitmap(int slot_id) { m_slot_id = slot_id; }

CUISlotBitmap::~CUISlotBitmap() {}

void CUISlotBitmap::OnLBtnDown(int x, int y) {
  if (m_parent) {
    m_parent->SendMsg(this, 13, (void*)m_slot_id, 0, 0, 0);
    m_parent->SendMsg(this, 6, (void*)m_id, 0, 0, 0);
  }
}

void* CUISlotBitmap::SendMsg(CUIWindow* sender, int message, void* val1,
                             void* val2, void* val3, void* val4) {
  void* result = NULL;

  if (message == 13) {
    m_state = (size_t)val1;
  } else {
    result = CUIWindow::SendMsg(sender, message, val1, val2, val3, val4);
  }
  return result;
}