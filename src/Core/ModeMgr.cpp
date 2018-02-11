#include "ModeMgr.h"
#include <string.h>
#include "Common/Globals.h"
#include "Common/modetype.h"
#include "Modes/GameMode.h"
#include "Modes/LoginMode.h"

CModeMgr::CModeMgr() { m_loop_cond = true; }

void CModeMgr::Run(int mode_type, const char* world_name) {
  m_cur_mode_type = mode_type;
  m_next_mode_type = mode_type;
  strncpy(m_cur_mode_name, world_name, sizeof(m_cur_mode_name));
  strncpy(m_next_mode_name, world_name, sizeof(m_next_mode_name));

  while (m_loop_cond) {
    if (g_sys_quit) return;
    m_cur_mode_type = m_next_mode_type;
    strncpy(m_cur_mode_name, m_next_mode_name, sizeof(m_cur_mode_name));

    if (m_cur_mode_type == MT_LOGIN)
      m_cur_mode = new CLoginMode();
    else if (m_cur_mode_type == MT_GAME)
      m_cur_mode = new CGameMode();

    m_cur_mode->OnInit(m_cur_mode_name);
    m_cur_mode->OnRun();
    m_cur_mode->OnExit();
    if (m_cur_mode) {
      delete m_cur_mode;
      m_cur_mode = NULL;
    }
  }
}

void CModeMgr::Switch(int mode_type, const char* mode_name) {
  m_cur_mode->SetLoopCond(false);
  strncpy(m_next_mode_name, mode_name, sizeof(m_next_mode_name));
  m_next_mode_type = mode_type;
}

void CModeMgr::Quit() {
  m_cur_mode->SetLoopCond(false);
  m_loop_cond = false;
}

CMode* CModeMgr::GetCurMode() { return m_cur_mode; }

CGameMode* CModeMgr::GetGameMode() {
  CGameMode* result;

  if (m_cur_mode_type == MT_GAME)
    result = (CGameMode*)m_cur_mode;
  else
    result = NULL;
  return result;
}

CLoginMode* CModeMgr::GetLoginMode() {
  CLoginMode* result;

  if (m_cur_mode_type == MT_LOGIN)
    result = NULL;
  else
    result = (CLoginMode*)m_cur_mode;
  return result;
}
