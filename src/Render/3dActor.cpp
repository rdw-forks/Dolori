#include "Render/3dActor.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Common/Globals.h"
#include "Common/debug.h"

C3dActor::C3dActor()
    : m_pos(),
      m_matrix_needs_update(true),
      m_shading_type(),
      m_textures(),
      m_name(),
      m_cur_motion(),
      m_anim_type(),
      m_anim_speed(),
      m_anim_len(),
      m_realbbmin(),
      m_realbbrange() {}

void C3dActor::AssignModel(CRsmRes *p_rsm_res) {
  m_shading_type = p_rsm_res->GetShadingType();
  const auto textures = p_rsm_res->GetTextures();

  m_textures.reserve(textures.size());
  for (const auto &texture_name : textures) {
    m_textures.push_back(g_TexMgr->GetTexture(texture_name, false));
  }

  m_root_node = p_rsm_res->GetRootNode();

  m_bbmin = glm::vec3(INT_MAX, INT_MAX, INT_MAX);
  m_bbmax = glm::vec3(INT_MIN, INT_MIN, INT_MIN);
  m_root_node->ComputeBoundingBox(m_bbmin, m_bbmax);
  m_bbrange = (m_bbmin + m_bbmax) / 2.0f;

  m_root_node->ComputeModelViewMatrix(this);
  m_root_node->ComputeNodeViewMatrix(this);

  m_realbbmax = glm::vec3(INT_MIN, INT_MIN, INT_MIN);
  m_realbbmin = glm::vec3(INT_MAX, INT_MAX, INT_MAX);
  const auto mat = glm::scale(glm::mat4(), glm::vec3(1, -1, 1));
  m_root_node->ComputeRealBoundingBox(mat, m_realbbmin, m_realbbmax);
  m_realbbrange = (m_realbbmax + m_realbbmin) / 2.0f;
}

void C3dActor::Render() {
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
    m_matrix_needs_update = false;
  }

  m_root_node->Render(this, glm::mat4());
}

void C3dActor::SetPos(const glm::vec3 &position) { m_pos = position; }

void C3dActor::SetRot(const glm::vec3 &rotation) { m_rot = rotation; }

void C3dActor::SetScale(const glm::vec3 &scale) { m_scale = scale; }

std::shared_ptr<CTexture> C3dActor::GetTexture(size_t id) const {
  if (id < m_textures.size()) {
    return m_textures[id];
  }

  return nullptr;
}

const glm::mat4 &C3dActor::GetModelViewMatrix() const {
  return m_modelview_matrix;
}

const glm::vec3 &C3dActor::GetBbRange() const { return m_bbrange; }

const glm::vec3 &C3dActor::GetBbMax() const { return m_bbmax; }

const glm::vec3 &C3dActor::GetBbMin() const { return m_bbmin; }
