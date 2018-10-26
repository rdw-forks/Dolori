#include "UI/UIServerListBox.h"

CUIServerListBox::CUIServerListBox(CUIWindowMgr* p_window_mgr)
    : CUIListBox(p_window_mgr), m_serverBalloon() {
  m_bR = 255;
  m_bG = 255;
  m_bB = 255;
  m_itemSpacing = 16;
}
