#ifndef DOLORI_CORE_MODEMGR_H_
#define DOLORI_CORE_MODEMGR_H_

#define _CRT_SECURE_NO_WARNINGS
#include <string>

#include "Modes/GameMode.h"
#include "Modes/LoginMode.h"
#include "Modes/Mode.h"
#include "Modes/modetype.h"

class CModeMgr {
 public:
  CModeMgr();

  void Run(ModeType, const char*);
  void Switch(ModeType modeType, const std::string& modeName);
  void Quit();
  CMode* GetCurMode();
  CGameMode* GetGameMode();
  CLoginMode* GetLoginMode();

 private:
  int m_loop_cond;
  CMode* m_cur_mode;
  std::string m_cur_mode_name;
  std::string m_next_mode_name;
  ModeType m_cur_mode_type;
  ModeType m_next_mode_type;
};

#endif  // DOLORI_CORE_MODEMGR_H_
