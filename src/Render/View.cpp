#include "View.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
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
  m_cur.at = glm::vec3(0.0f);
  m_dest.at = glm::vec3(0.0f);
  m_up = glm::vec3(0.0f);
}

void CView::OnCalcViewInfo() {
  // m_dest.at = m_world->GetPlayer()->GetPos();
  // InterpolateViewInfo();
  // ProcessQuake();
  // BuildViewMatrix();
  glm::mat4 projection = glm::perspective(70.0, 640.0 / 480.0, 1.0, 2000.0);

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(projection));

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // gluLookAt(390.0, 10.0, -480.0, 390.0, 0.0, -480.0, 0.0, 1.0, 0.0);
  gluLookAt(-100.0, -100.0, 10.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0);
}

void CView::OnRender() {
  // float hratio = g_Renderer->GetHorizontalRatio();
  // float vratio = g_Renderer->GetVerticalRatio();

  // m_view_frustum.Build(hratio, vratio, m_view_matrix, NULL);
}
