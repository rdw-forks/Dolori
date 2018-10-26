#include "Modes/Mode.h"

#include "Common/Globals.h"

CMode::CMode(CRagConnection* p_rag_connection, CUIWindowMgr* p_window_mgr)
    : m_sub_mode(),
      m_sub_mode_cnt(),
      m_next_sub_mode(),
      m_fadeInCount(),
      m_loop_cond(true),
      m_isConnected(),
      p_rag_connection_(p_rag_connection),
      p_window_mgr_(p_window_mgr) {}

void* CMode::SendMsg(size_t msg, const void* val1, const void* val2,
                     const void* val3) {
  switch (msg) {
    case MM_QUIT:
      g_ModeMgr->Quit();
      break;
    case MM_SCREENSHOT:
      m_screenShotNow = true;
      break;
  };

  return nullptr;
}

bool CMode::GetLoopCond() const { return m_loop_cond; }

void CMode::SetLoopCond(bool loop_cond) { m_loop_cond = loop_cond; }
