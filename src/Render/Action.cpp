#include "Render/Action.h"

CAction::CAction() : m_motions() {}

void CAction::Create(unsigned int motion_count) {
  m_motions.resize(motion_count);
}

void CAction::SetMotion(size_t motion_id, CMotion motion) {
  m_motions[motion_id] = std::move(motion);
}

const CMotion* CAction::GetMotion(size_t motion_id) const {
  if (motion_id < m_motions.size()) {
    return &m_motions[motion_id];
  }

  return nullptr;
}
