#include "ModeMgr.h"
#include <string.h>
#include "../Common/Globals.h"
#include "../Common/modetype.h"
#include "../Modes/GameMode.h"
#include "../Modes/LoginMode.h"

CModeMgr::CModeMgr() { m_loopCond = true; }

void CModeMgr::Run(int mode_type, const char* world_name) {
  m_curModeType = mode_type;
  m_nextModeType = mode_type;
  strncpy_s(m_curModeName, world_name, sizeof(m_curModeName));
  strncpy_s(m_nextModeName, world_name, sizeof(m_nextModeName));

  while (m_loopCond) {
    if (g_sysQuit) return;
    m_curModeType = m_nextModeType;
    strncpy_s(m_curModeName, m_nextModeName, sizeof(m_curModeName));

    if (m_curModeType == MT_LOGIN)
      m_curMode = new CLoginMode();
    else if (m_curModeType == MT_GAME)
      m_curMode = new CGameMode();

    if (m_curMode) {
      m_curMode->OnInit(m_curModeName);
      m_curMode->OnRun();
      m_curMode->OnExit();
      delete m_curMode;
    }
  }
}

void CModeMgr::Switch(int modeType, const char* modeName) {
  m_curMode->SetLoopCond(false);
  strncpy_s(m_nextModeName, modeName, 40);
  m_nextModeType = modeType;
}

void CModeMgr::Quit() {
  m_curMode->SetLoopCond(false);
  /*if (g_serviceType == 11)
          ShellExecuteA(g_hMainWnd, Operation, aHttpWww_ragnar, 0, 0, 1);*/
  m_loopCond = false;
}

CMode* CModeMgr::GetCurMode() { return m_curMode; }

CGameMode* CModeMgr::GetGameMode() {
  CGameMode* result;

  if (m_curModeType == MT_GAME)
    result = (CGameMode*)m_curMode;
  else
    result = NULL;
  return result;
}

CLoginMode* CModeMgr::GetLoginMode() {
  CLoginMode* result;

  if (m_curModeType == MT_LOGIN)
    result = NULL;
  else
    result = (CLoginMode*)m_curMode;
  return result;
}