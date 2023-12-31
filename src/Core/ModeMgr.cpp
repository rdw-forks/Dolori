#include "Core/ModeMgr.h"

#include "Common/Globals.h"
#include "Modes/GameMode.h"
#include "Modes/LoginMode.h"

CModeMgr::CModeMgr()
    : m_cur_mode(),
      m_loop_cond(true),
      m_cur_mode_type(),
      rag_connection_(),
      window_mgr_() {}

void CModeMgr::Init() {
  window_mgr_.SetSize(g_Renderer->GetWidth(), g_Renderer->GetHeight());
  window_mgr_.InvalidateUpdateNeededUI();
}

void CModeMgr::Run(ModeType mode_type, const std::string& map_name) {
  m_cur_mode_type = mode_type;
  m_next_mode_type = mode_type;
  m_cur_mode_name = map_name;
  m_next_mode_name = map_name;

  while (m_loop_cond && !g_sys_quit) {
    m_cur_mode_type = m_next_mode_type;
    m_cur_mode_name = m_next_mode_name;

    if (m_cur_mode_type == ModeType::kLogin) {
      m_cur_mode = new CLoginMode(&rag_connection_, &window_mgr_);
    } else if (m_cur_mode_type == ModeType::kGame) {
      m_cur_mode = new CGameMode(&rag_connection_, &window_mgr_);
    }

    m_cur_mode->OnInit(m_cur_mode_name);
    m_cur_mode->OnRun();
    m_cur_mode->OnExit();

    if (m_cur_mode != nullptr) {
      delete m_cur_mode;
      m_cur_mode = nullptr;
    }
  }
}

void CModeMgr::Switch(ModeType mode_type, const std::string& map_name) {
  m_cur_mode->SetLoopCond(false);
  m_next_mode_name = map_name;
  m_next_mode_type = mode_type;
}

void CModeMgr::Quit() { m_cur_mode->SetLoopCond(false); }

CMode* CModeMgr::GetCurMode() const { return m_cur_mode; }

CGameMode* CModeMgr::GetGameMode() const {
  if (m_cur_mode_type == ModeType::kGame) {
    // We can downcast safely with static_cast since cur_mode_type is set
    return static_cast<CGameMode*>(m_cur_mode);
  }

  return nullptr;
}

CLoginMode* CModeMgr::GetLoginMode() const {
  if (m_cur_mode_type == ModeType::kLogin) {
    // We can downcast safely with static_cast since cur_mode_type is set
    return static_cast<CLoginMode*>(m_cur_mode);
  }

  return nullptr;
}
