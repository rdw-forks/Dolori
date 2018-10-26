#ifndef DOLORI_CORE_MODEMGR_H_
#define DOLORI_CORE_MODEMGR_H_

#include <string>

#include "Core/UIWindowMgr.h"
#include "Modes/GameMode.h"
#include "Modes/LoginMode.h"
#include "Modes/Mode.h"
#include "Network/RagConnection.h"

class CModeMgr {
 public:
  CModeMgr();

  void Init();
  void Run(ModeType mode_type, const std::string& map_name);
  void Switch(ModeType mode_type, const std::string& map_name);
  void Quit();
  CMode* GetCurMode() const;
  CGameMode* GetGameMode() const;
  CLoginMode* GetLoginMode() const;

 private:
  bool m_loop_cond;
  CMode* m_cur_mode;
  std::string m_cur_mode_name;
  std::string m_next_mode_name;
  ModeType m_cur_mode_type;
  ModeType m_next_mode_type;
  CRagConnection rag_connection_;
  CUIWindowMgr window_mgr_;
};

#endif  // DOLORI_CORE_MODEMGR_H_
