#include "Render/Action.h"

CAction::CAction() : m_motions() {}

CAction::~CAction() {}

void CAction::Create(unsigned int motion_count) {
  m_motions.resize(motion_count);
}

CMotion* CAction::GetMotion(unsigned int motion_number) {
  if (motion_number < m_motions.size()) {
    return &m_motions[motion_number];
  }
  return nullptr;
}
