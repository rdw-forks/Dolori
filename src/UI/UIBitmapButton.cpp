#include "UI/UIBitmapButton.h"

#include "Common/Globals.h"
#include "UI/UIBmp.h"

CUIBitmapButton::CUIBitmapButton(CUIWindowMgr* p_window_mgr)
    : CUIButton(p_window_mgr), m_bitmapWidth(), m_bitmapHeight() {}

void CUIBitmapButton::SetBitmapName(const std::string& bitmapName,
                                    size_t buttonState) {
  const char* resource_name;

  resource_name = UIBmp(bitmapName);
  const auto resource =
      static_cast<CBitmapRes*>(g_ResMgr->Get(resource_name, false));
  if (!resource) {
    return;
  }

  if (resource->GetWidth() > m_bitmapWidth) {
    m_bitmapWidth = resource->GetWidth();
  }

  if (resource->GetHeight() > m_bitmapHeight) {
    m_bitmapHeight = resource->GetHeight();
  }

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
  }
}

int CUIBitmapButton::GetBitmapWidth() const { return m_bitmapWidth; }

int CUIBitmapButton::GetBitmapHeight() const { return m_bitmapHeight; }

void CUIBitmapButton::OnDraw() {
  const auto bitmap_name = [&]() -> std::string {
    switch (m_state) {
      case 0:
        return UIBmp(m_normalBitmapName);
      case 1:
        return UIBmp(m_mouseonBitmapName);
      case 2:
        return UIBmp(m_pressedBitmapName);
      default:
        return {};
    }
  }();

  const auto bitmap =
      static_cast<CBitmapRes*>(g_ResMgr->Get(bitmap_name, false));
  if (bitmap != nullptr) {
    DrawBitmap(0, 0, bitmap, 0);
  }
}
