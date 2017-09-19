#include "Action.h"

CAction::CAction() {}

CAction::~CAction() {}

void CAction::Create(unsigned int motion_count) {
  motions.resize(motion_count);
}

CMotion* CAction::GetMotion(unsigned int motion_number) {
  if (motion_number < motions.size())
    return &motions[motion_number];
  else
    return NULL;
}
