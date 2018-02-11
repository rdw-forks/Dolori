#include "View.h"
#include "Common/Globals.h"

CView::CView() {
  m_cur.longitude = 0.0f;
  m_is_quake = false;
  m_skybox = NULL;
  m_quake_start_tick = 0;
  m_is_FPS_mode = false;
}

CView::~CView() {}

void CView::OnEnterFrame() {
  m_cur.distance = 300.0f;
  m_dest.distance = 300.0f;
  m_cur.longitude = 0.f;
  m_dest.longitude = 0.f;
  m_cur.latitude = -45.0f;
  m_dest.latitude = -45.0f;
  m_cur.at = vec3(0.0f);
  m_dest.at = vec3(0.0f);
  m_up = vec3(0.0f);
}

void CView::OnCalcViewInfo() {
  // m_dest.at = m_world->GetPlayer()->GetPos();
  // InterpolateViewInfo();
  // ProcessQuake();
  // BuildViewMatrix();
}

void CView::OnRender() {
  float hratio = g_Renderer->GetHorizontalRatio();
  float vratio = g_Renderer->GetVerticalRatio();

  m_view_frustum.Build(hratio, vratio, m_view_matrix, NULL);
  // m_world->Render();
}
