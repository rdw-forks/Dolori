#include "UIWindow.h"
#include "../Common/GetTick.h"

CUIWindow::CUIWindow() {
  m_x = 0;
  m_y = 0;
  m_w = 0;
  m_h = 0;
  m_parent = NULL;
  m_state = 0;
  m_stateCnt = 0;
  m_surface = NULL;
  m_isDirty = true;
  m_id = 117;
  m_show = true;
  m_trans = 255;
  m_transTarget = 255;
  m_transTime = GetTick();
}

CUIWindow::~CUIWindow() {}

void CUIWindow::Create(int cx, int cy) {
  if (m_surface) delete m_surface;
  m_surface = new CSurface();
  m_w = cx;
  m_h = cy;
  OnCreate(cx, cy);
  OnSize(cx, cy);
}

void CUIWindow::Move(int x, int y) {
  m_x = x;
  m_y = y;
}

void CUIWindow::OnDraw() {}

void CUIWindow::OnCreate(int, int) {}

void CUIWindow::OnSize(int, int) {}

bool CUIWindow::IsUpdateNeeded() { return true; }

bool CUIWindow::IsShow() { return m_show; }

void CUIWindow::SetShow(bool show) { m_show = show; }

void CUIWindow::AddChild(CUIWindow* wnd) {
  wnd->m_parent = this;
  m_children.push_back(wnd);
}

void CUIWindow::DoDraw() {
  if (m_isDirty) {
    OnDraw();
    m_isDirty = false;
  }
  DrawSurface();

  for (auto it = m_children.begin(); it != m_children.end(); ++it) {
    CUIWindow* wnd = *it;
    wnd->DoDraw();
  }
}

void CUIWindow::DrawBitmap(int x, int y, CBitmapRes* bitmap,
                           int drawOnlyNoTrans) {
  if (m_surface && bitmap) {
    m_surface->Update(x, y, bitmap->GetWidth(), bitmap->GetHeight(),
                      bitmap->GetData(), drawOnlyNoTrans);
  }
}

void CUIWindow::DrawSurface() {
  int x = m_x;
  int y = m_y;

  if (m_parent) {
    x += m_parent->m_x;
    y += m_parent->m_y;
  }
  m_surface->DrawSurface(x, y, m_w, m_h, 0xFFFFFFFF);
}

void CUIWindow::InvalidateChildren() {
  m_isDirty = true;
  for (auto it = m_children.begin(); it != m_children.end(); ++it) {
    if ((*it)->IsUpdateNeeded()) (*it)->InvalidateChildren();
  }
}

void CUIWindow::SetId(int id) { m_id = id; }

int CUIWindow::GetId() { return m_id; }
