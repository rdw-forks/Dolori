#include "GameObject/RenderObject.h"

CRenderObject::CRenderObject() : CGameObject(), m_pos() {}

const glm::vec3& CRenderObject::GetPos() const { return m_pos; }
