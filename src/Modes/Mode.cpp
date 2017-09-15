#include "Mode.h"
#include "../Common/Globals.h"

CMode::CMode() {}

CMode::~CMode() {}

bool CMode::GetLoopCond() { return m_loopCond; }

void CMode::SetLoopCond(bool loop_cond) { m_loopCond = loop_cond; }

void CMode::OnInit(const char*) {}

int CMode::OnRun() { return 0; }

void CMode::OnExit() {}

int CMode::SendMsg(size_t messageId, void* val1, void* val2, void* val3) {
  if (messageId == 2) {
    g_ModeMgr->Quit();
  } else if (messageId == 75) {
    m_screenShotNow = true;
  }
  return 0;
}