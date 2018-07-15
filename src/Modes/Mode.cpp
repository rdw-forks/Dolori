#include "Modes/Mode.h"

#include "Common/Globals.h"

CMode::CMode()
    : m_sub_mode(),
      m_sub_mode_cnt(),
      m_next_sub_mode(),
      m_fadeInCount(),
      m_loop_cond(true),
      m_isConnected() {}

bool CMode::GetLoopCond() { return m_loop_cond; }

void CMode::SetLoopCond(bool loop_cond) { m_loop_cond = loop_cond; }

void* CMode::SendMsg(size_t msg, const void* val1, const void* val2, const void* val3) {
  void* result = nullptr;

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
