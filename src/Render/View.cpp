#include "View.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Common/Globals.h"

CView::CView()
    : m_is_FPS_mode(false),
      m_cur(),
      m_from(),
      m_up(),
      m_view_matrix(),
      m_inv_view_matrix(),
      m_skybox() {}

CView::~CView() {}

void CView::AddLongitude(double delta) { m_cur.longitude += delta; }

void CView::AddLatitude(double delta) { m_cur.latitude += delta; }

void CView::AddDistance(double delta) { m_cur.distance += delta; }

const glm::mat4& CView::GetViewMatrix() { return m_view_matrix; }

void CView::OnEnterFrame() {
  m_cur.distance = 300.0;
  m_cur.longitude = 0.0;
  m_cur.latitude = -45.0;
  m_cur.at = glm::vec3(0.0);
  m_from = m_cur.at + glm::vec3(-m_cur.distance, -m_cur.distance, 0.0);
  m_up = glm::vec3(0.0, -1.0, 0.0);
}

void CView::OnCalcViewInfo(const glm::vec3& player_pos) {
  m_cur.at = player_pos;
  m_from = m_cur.at + glm::vec3(-m_cur.distance, -m_cur.distance, 0.0);
  // InterpolateViewInfo();
  BuildViewMatrix();
}

void CView::OnRender() {
  // float hratio = g_Renderer->GetHorizontalRatio();
  // float vratio = g_Renderer->GetVerticalRatio();

  // m_view_frustum.Build(hratio, vratio, m_view_matrix, NULL);
}

void CView::BuildViewMatrix() {
  glm::quat q =
      glm::angleAxis(static_cast<float>(glm::radians(-m_cur.longitude)),
                     glm::vec3(0.0, 0.0, 1.0)) *
      glm::angleAxis(static_cast<float>(glm::radians(m_cur.latitude)),
                     glm::vec3(0.0, 1.0, 0.0));
  m_view_matrix = glm::lookAt(m_from, m_cur.at, m_up) * glm::mat4_cast(q);

  // g_Renderer->SetLookAt(m_from, m_cur.at, m_up);
  // glm::mat4 view = glm::lookAt(m_from, m_cur.at, m_up);
  g_Renderer->SetViewMatrix(m_view_matrix);
}
