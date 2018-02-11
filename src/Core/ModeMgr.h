#ifndef DOLORI_CORE_MODEMGR_H_
#define DOLORI_CORE_MODEMGR_H_

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include "Modes/GameMode.h"
#include "Modes/LoginMode.h"
#include "Modes/Mode.h"

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
  int m_loop_cond;
  CMode* m_cur_mode;
  std::string m_cur_mode_name;
  std::string m_next_mode_name;
  int m_cur_mode_type;
  int m_next_mode_type;
};

#endif  // DOLORI_CORE_MODEMGR_H_
