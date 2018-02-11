#include "ModeMgr.h"
#include <string.h>
#include "Common/Globals.h"
#include "Common/modetype.h"
#include "Modes/GameMode.h"
#include "Modes/LoginMode.h"

CModeMgr::CModeMgr() : m_loop_cond(true) {}

void CModeMgr::Run(int mode_type, const char* world_name) {
  m_cur_mode_type = mode_type;
  m_next_mode_type = mode_type;
  m_cur_mode_name = world_name;
  m_next_mode_name = world_name;

  while (m_loop_cond && !g_sys_quit) {
    m_cur_mode_type = m_next_mode_type;
    m_cur_mode_name = m_next_mode_name;

    if (m_cur_mode_type == ModeType::kLogin) {
      m_cur_mode = new CLoginMode();
    } else if (m_cur_mode_type == ModeType::kGame) {
      m_cur_mode = new CGameMode();
    }

    m_cur_mode->OnInit(m_cur_mode_name.c_str());
    m_cur_mode->OnRun();
    m_cur_mode->OnExit();

    if (m_cur_mode) {
      delete m_cur_mode;
      m_cur_mode = nullptr;
    }
  }
}

void CModeMgr::Switch(int mode_type, const char* mode_name) {
  m_cur_mode->SetLoopCond(false);
  m_next_mode_name = mode_name;
  m_next_mode_type = mode_type;
}

void CModeMgr::Quit() {
  m_cur_mode->SetLoopCond(false);
  m_loop_cond = false;
}

CMode* CModeMgr::GetCurMode() { return m_cur_mode; }

CGameMode* CModeMgr::GetGameMode() {
  if (m_cur_mode_type == ModeType::kGame) {
    return reinterpret_cast<CGameMode*>(m_cur_mode);
  }

  return nullptr;
}

CLoginMode* CModeMgr::GetLoginMode() {
  if (m_cur_mode_type == ModeType::kLogin) {
    return reinterpret_cast<CLoginMode*>(m_cur_mode);
  }

  return nullptr;
}
