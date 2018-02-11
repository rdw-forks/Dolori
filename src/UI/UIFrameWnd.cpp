#include "UIFrameWnd.h"
#include "Common/GetTick.h"
#include "Common/Globals.h"

CUIFrameWnd::CUIFrameWnd() {}

CUIFrameWnd::~CUIFrameWnd() {}

void CUIFrameWnd::OnLBtnDown(int x, int y) {
  if (this) {
    int gx, gy;

    g_WindowMgr->SetCapture(this);
    GetGlobalCoor(&gx, &gy);
    gx += x;
    gy += y;
    m_startGlobalX = gx;
    m_startGlobalY = gy;
    m_orgX = m_x;
    m_orgY = m_y;
    m_transTarget = 128;
    m_transTime = GetTick();
    // g_SnapMgr->BeginMove(this);
  }
}

void CUIFrameWnd::OnLBtnUp(int x, int y) {
  if (g_WindowMgr->GetCapture() == this) {
    m_transTarget = 255;
    m_transTime = GetTick();
    g_WindowMgr->ReleaseCapture();
    // CSnapMgr::EndMove(&g_snapMgr, (UIWindow *)&v3->vfptr);
  }
}

void* CUIFrameWnd::SendMsg(CUIWindow* sender, int message, void* val1,
                           void* val2, void* val3, void* val4) {
  void* result;

  switch (message) {
    default:
      result = CUIWindow::SendMsg(sender, message, val1, val2, val3, val4);
  };

  return result;
}
