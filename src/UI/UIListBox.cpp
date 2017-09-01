#include "UIListBox.h"

CUIListBox::CUIListBox() {}

CUIListBox::~CUIListBox() {}

void CUIListBox::OnCreate(int, int) {}

void CUIListBox::AddItem(const char *txt) {
  m_items.push_back(txt);
}
