#include "UIBitmapButton.h"
#include "../Common/Globals.h"
#include "../Common/service_type.h"
#include "UIBmp.h"
#include <iostream>

CUIBitmapButton::CUIBitmapButton() {
  m_state = 0;
  m_isDisabled = 0;
  m_bitmapWidth = 0;
  m_bitmapHeight = 0;
}

CUIBitmapButton::~CUIBitmapButton() {}

void CUIBitmapButton::SetBitmapName(const char* bitmapName, int buttonState) {
  const char* resource_name;
  CBitmapRes* resource;

  resource_name = UIBmp(bitmapName);
  resource = (CBitmapRes*)g_ResMgr->Get(resource_name, false);
  if (resource) {
    if (resource->GetWidth() > m_bitmapWidth)
      m_bitmapWidth = resource->GetWidth();
    if (resource->GetHeight() > m_bitmapHeight)
      m_bitmapHeight = resource->GetHeight();

    switch (buttonState) {
      case BTN_NONE:
        m_normalBitmapName = bitmapName;
        break;
      case BTN_DOWN:
        m_mouseonBitmapName = bitmapName;
        break;
      case BTN_PRESSED:
        m_pressedBitmapName = bitmapName;
        break;
    };
  }
}

int CUIBitmapButton::GetBitmapWidth() { return m_bitmapWidth; }

int CUIBitmapButton::GetBitmapHeight() { return m_bitmapHeight; }

void CUIBitmapButton::OnDraw() {
  if (m_state == BTN_NONE) {
    const char* bitmap_name = UIBmp(m_normalBitmapName.c_str());
    CBitmapRes* bitmap = (CBitmapRes*)g_ResMgr->Get(bitmap_name, false);
    DrawBitmap(0, 0, bitmap, 0);
    return;
  }
}
