#include "Mode.h"

CMode::CMode() {}

CMode::~CMode() {}

bool CMode::GetLoopCond() { return m_loopCond; }

void CMode::SetLoopCond(bool loop_cond) { m_loopCond = loop_cond; }

void CMode::OnInit(const char *) {}

int CMode::OnRun() { return 0; }

void CMode::OnExit() {}