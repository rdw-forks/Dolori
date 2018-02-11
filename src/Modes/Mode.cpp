#include "Mode.h"
#include "Common/Globals.h"

CMode::CMode() {}

CMode::~CMode() {}

bool CMode::GetLoopCond() { return m_loop_cond; }

void CMode::SetLoopCond(bool loop_cond) { m_loop_cond = loop_cond; }

void CMode::OnInit(const char*) {}

int CMode::OnRun() { return 0; }

void CMode::OnExit() {}

void* CMode::SendMsg(size_t msg, void* val1, void* val2, void* val3) {
  void* result = NULL;

  switch (msg) {
    case MM_QUIT:
      g_ModeMgr->Quit();
      break;
    case MM_SCREENSHOT:
      m_screenShotNow = true;
      break;
  };

  return result;
}