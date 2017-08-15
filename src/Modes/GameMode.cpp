#include "GameMode.h"
#include "../Common/Globals.h"
#include "../Common/talktype.h"
#include "../Common/GetTick.h"

CGameMode::CGameMode() {}

void CGameMode::Intialize() {
  m_noMove = 0;
  m_isOnQuest = 0;
  m_isPlayerDead = 0;
  m_nameBalloon = 0;
  m_targetNameBalloon = 0;
  m_broadcastBalloon = 0;
  m_skillNameBalloon = 0;
  m_skillMsgBalloon = 0;
  m_skillUsedMsgBalloon = 0;
  m_playerGage = 0;
  m_nameActorAid = 0;
  m_nameBalloonWidth = 0;
  m_nameBalloonHeight = 0;
  m_nameDisplayed = 1;
  m_nameDisplayed2 = 1;
  m_waitingUseItemAck = 0;
  m_waitingItemThrowAck = 0;
  m_waitingReqStatusAck = 0;
  //m_dragInfo.m_dragType = 0;
  //m_dragInfo.m_dragItemIndex = 0;
  //m_dragInfo.m_numDragItem = 0;
  //m_dragInfo.m_slotNum = -1;
  //m_dragInfo.m_isIdentified = 0;
  m_lastNaid = 0;
  m_menuTargetAID = 0;
  m_lastPcGid = 0;
  m_lastMonGid = 0;
  m_lastLockOnMonGid = 0;
  m_isAutoMoveClickOn = 1;
  m_isWaitingWhisperSetting = 0;
  m_isWaitingEnterRoom = 0;
  m_isWaitingAddExchangeItem = 0;
  m_waitingWearEquipAck = GetTick() - 2000;
  m_isWaitingCancelExchangeItem = 0;
  m_waitingTakeoffEquipAck = GetTick() - 2000;
  m_isReqUpgradeSkillLevel = 0;
  m_exchangeItemCnt = 0;
  m_sameChatRepeatCnt = 0;
  m_numNotifyTime = 0;
}

void CGameMode::OnInit(const char *) {
  m_posOfBossMon.x = -1;
  m_posOfBossMon.y = -1;
  m_isBossAlarm = 0;
  m_onCopyName = 0;

  Intialize();
  auto name_list = g_Session->GetNumExNameList();
  if (!name_list.empty()) {
    for (auto it = name_list.begin(); it != name_list.end(); ++it) {
      ProcessTalkType(TT_REQ_WHISPER_PC_EX, *it);
    }
  }
  m_isCtrlLock = 0;
  m_showTimeStartTick = 0;
  m_autoSaveChatCnt = 0;
  m_recordChatNum = 0;
  m_strikeNum = 0;

  if (g_Session->IsMasterAid(7)) {
    // Now Auto chat Save System is ENABLED.
  }
}

int CGameMode::OnRun() {
  while (m_loopCond) {
    if (g_sysQuit) break;
    if (true /*!dword_7687C8*/) {
      if (m_nextSubMode != -1) {
        m_subMode = m_nextSubMode;
        m_subModeCnt = 0;
        m_nextSubMode = -1;
        OnChangeState(m_nextSubMode);
      }
    }
    OnUpdate();
  }
  // RunFadeOut(0);
  return 1;
}

void CGameMode::OnExit() {}

void CGameMode::OnUpdate() {
  // m_scheduler->OnRun()
  // ProcessDamageSituation()
}

void CGameMode::OnChangeState(int state) {}

void CGameMode::ProcessTalkType(int talktype, const std::string &string) {
  switch (talktype) {
    case TT_REQ_WHISPER_PC_EX:
      break;
  };
}