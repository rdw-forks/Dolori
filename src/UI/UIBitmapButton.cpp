#include "UI/UIBitmapButton.h"

#include "Common/Globals.h"
#include "Common/service_type.h"
#include "UI/UIBmp.h"

CUIBitmapButton::CUIBitmapButton() : m_bitmapWidth(), m_bitmapHeight() {}

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
      case 0:
        m_normalBitmapName = bitmapName;
        break;
      case 1:
        m_mouseonBitmapName = bitmapName;
        break;
      case 2:
        m_pressedBitmapName = bitmapName;
        break;
    };
  }
}

int CUIBitmapButton::GetBitmapWidth() { return m_bitmapWidth; }

int CUIBitmapButton::GetBitmapHeight() { return m_bitmapHeight; }

void CUIBitmapButton::OnDraw() {
  const char* bitmap_name;
  CBitmapRes* bitmap;

  if (m_state == 0)
    bitmap_name = UIBmp(m_normalBitmapName.c_str());
  else if (m_state == 1)
    bitmap_name = UIBmp(m_mouseonBitmapName.c_str());
  else if (m_state == 2)
    bitmap_name = UIBmp(m_pressedBitmapName.c_str());

  bitmap = (CBitmapRes*)g_ResMgr->Get(bitmap_name, false);
  DrawBitmap(0, 0, bitmap, 0);
}
