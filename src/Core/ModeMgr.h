#ifndef DOLORI_CORE_MODEMGR_H_
#define DOLORI_CORE_MODEMGR_H_

#define _CRT_SECURE_NO_WARNINGS
#include "../Modes/GameMode.h"
#include "../Modes/LoginMode.h"
#include "../Modes/Mode.h"

class CModeMgr {
 public:
  CModeMgr();

  void Run(int, const char*);
  void Switch(int modeType, const char* modeName);
  void Quit();
  CMode* GetCurMode();
  CGameMode* GetGameMode();
  CLoginMode* GetLoginMode();

 private:
  int m_loopCond;
  CMode* m_curMode;
  char m_curModeName[0x28];
  char m_nextModeName[0x28];
  int m_curModeType;
  int m_nextModeType;
};

#endif  // DOLORI_CORE_MODEMGR_H_
