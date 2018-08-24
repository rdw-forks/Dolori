#include "Render/3dActor.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Common/debug.h"

C3dActor::C3dActor()
    : m_pos(), m_matrix_needs_update(true), m_realbbmin(), m_realbbrange() {}

void C3dActor::AssignModel(CRsmRes *p_rsm_res) {
  m_root_node = p_rsm_res->GetRootNode();

  m_bbmin = glm::vec3(999999, 999999, 999999);
  m_bbmax = glm::vec3(-999999, -999999, -9999999);
  m_root_node->ComputeBoundingBox(m_bbmin, m_bbmax);
  m_bbrange = (m_bbmin + m_bbmax) / 2.0f;

  m_root_node->ComputeModelViewMatrix();

  m_realbbmax = glm::vec3(-999999, -999999, -999999);
  m_realbbmin = glm::vec3(999999, 999999, 999999);
  auto mat = glm::scale(glm::mat4(), glm::vec3(1, -1, 1));
  m_root_node->ComputeRealBoundingBox(mat, m_realbbmin, m_realbbmax);
  m_realbbrange = (m_realbbmax + m_realbbmin) / 2.0f;
}

void C3dActor::Render(const glm::mat4 &matrix, unsigned char, int) {
  if (m_matrix_needs_update) {
    m_modelview_matrix = glm::mat4();
    m_modelview_matrix = glm::translate(m_modelview_matrix, m_pos);
    m_modelview_matrix = glm::rotate(m_modelview_matrix, glm::radians(m_rot.z),
                                     glm::vec3(0, 0, 1));
    m_modelview_matrix = glm::rotate(m_modelview_matrix, glm::radians(m_rot.x),
                                     glm::vec3(1, 0, 0));
    m_modelview_matrix = glm::rotate(m_modelview_matrix, glm::radians(m_rot.y),
                                     glm::vec3(0, 1, 0));
    m_modelview_matrix = glm::scale(m_modelview_matrix, m_scale);
    m_modelview_matrix = glm::translate(
        m_modelview_matrix,
        glm::vec3(-m_realbbrange.x, m_realbbmin.y, -m_realbbrange.z));
    m_matrix_needs_update = true;
  }

  m_root_node->Render(m_modelview_matrix, 0, 0);
}

void C3dActor::SetPos(const glm::vec3 &position) { m_pos = position; }

void C3dActor::SetRot(const glm::vec3 &rotation) { m_rot = rotation; }

void C3dActor::SetScale(const glm::vec3 &scale) { m_scale = scale; }
