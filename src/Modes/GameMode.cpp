#include "Modes/GameMode.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "Common/GetTick.h"
#include "Common/Globals.h"
#include "Common/debug.h"
#include "Common/talktype.h"
#include "Input/Mouse.h"
#include "Input/SDLEvents.h"
#include "Network/Packets.h"
#include "Render/View.h"
#include "Render/World.h"

CGameMode::CGameMode() : CMode(), m_world(), m_view() {}

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
  // m_dragInfo.m_dragType = 0;
  // m_dragInfo.m_dragItemIndex = 0;
  // m_dragInfo.m_numDragItem = 0;
  // m_dragInfo.m_slotNum = -1;
  // m_dragInfo.m_isIdentified = 0;
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

void CGameMode::OnInit(const char *mode_name) {
  m_posOfBossMon.x = -1;
  m_posOfBossMon.y = -1;
  m_isBossAlarm = 0;
  m_onCopyName = 0;
  strncpy(m_rsw_name, mode_name, sizeof(m_rsw_name));

  g_Renderer->Clear(true);
  g_WindowMgr->SetWallpaper(nullptr);
  g_WindowMgr->RenderWallPaper();
  if (g_Renderer->DrawScene()) {
    g_Renderer->Flip();
  }

  m_view.OnEnterFrame();
  m_world.OnEnterFrame();
  m_isCheckGndAlpha = 0;
  // SetCamera();
  // m_mousePointer = new CMousePointer();
  Intialize();
  auto name_list = g_Session->GetNumExNameList();
  for (const auto &name : name_list) {
    ProcessTalkType(TT_REQ_WHISPER_PC_EX, name);
  }
  m_is_ctrl_lock = 0;
  m_show_time_start_tick = 0;
  m_auto_save_chat_cnt = 0;
  m_record_chat_num = 0;
  m_strike_num = 0;

  if (g_Session->IsMasterAid(7)) {
    // Now Auto chat Save System is ENABLED.
  }
}

int CGameMode::OnRun() {
  while (m_loop_cond && !g_sys_quit) {
    if (m_next_sub_mode != -1) {
      m_sub_mode = m_next_sub_mode;
      m_sub_mode_cnt = 0;
      m_next_sub_mode = -1;
      OnChangeState(m_sub_mode);
    }
    OnUpdate();
  }
  // RunFadeOut(0);
  return 1;
}

void CGameMode::OnExit() {}

void CGameMode::OnUpdate() {
  // PollNetworkStatus();

  // m_scheduler->OnRun()
  // ProcessDamageSituation()

  g_Renderer->Clear(false);
  g_Renderer->ClearBackground();
  if (m_loop_cond) {
    ProcessInput();
    // m_world->ProcessActors();
    m_view.OnCalcViewInfo(m_world.GetPlayer().GetPos());
  }

  m_view.OnRender();
  m_world.Render();
  if (g_Renderer->DrawScene()) {
    g_Renderer->Flip();
  }
}

void CGameMode::OnChangeState(int state) {}

void CGameMode::ProcessTalkType(int talktype, const std::string &string) {
  switch (talktype) {
    case TT_REQ_WHISPER_PC_EX:
      break;
  };
}

void *CGameMode::SendMsg(size_t msg, const void *val1, const void *val2,
                         const void *val3) {
  switch (msg) {
    case MM_QUERYRSWNAME:
      return m_rsw_name;
      break;
  };

  return nullptr;
}

void CGameMode::ProcessInput() {
  ProcessSDLEvents();
  g_Mouse->ReadState();
  int process_type = g_WindowMgr->ProcessInput();
  // g_WindowMgr->OnProcess();
  // ProcessNameBalloon(v1);
  // ProcessHelpBalloon();
  ProcessRightButton();
  ProcessMouseWheel(process_type);
  // ProcessKeyBoard();
  // ProcessReqEmblem(v1);

  m_oldMouseX = g_Mouse->GetXPos();
  m_oldMouseY = g_Mouse->GetYPos();
}

void CGameMode::ProcessRightButton() {
  CMouse::ButtonState button_state = g_Mouse->GetRBtn();
  const double kSensitivity = 0.8;

  if (button_state == CMouse::ButtonState::kDown) {
    // m_rBtnClickX = g_Mouse->GetXPos();
    // m_rBtnClickY = g_Mouse->GetYPos();
    m_view.AddLongitude((g_Mouse->GetYPos() - m_oldMouseY) * kSensitivity);
    m_view.AddLatitude(-(g_Mouse->GetXPos() - m_oldMouseX) * kSensitivity);
  } else {
  }
}

void CGameMode::ProcessMouseWheel(int process_type) {
  const double kSensitivity = 10.0;

  m_view.AddDistance(g_Mouse->GetWheel() * kSensitivity);
}
void CGameMode::PollNetworkStatus() {
  char buffer[2048];

  if (!g_RagConnection->Poll()) g_ModeMgr->GetCurMode()->SendMsg(1, 0, 0, 0);

  if (g_mustPumpOutReceiveQueue) {
    unsigned int aid;
    if (g_RagConnection->Recv((char *)&aid, 4, 1))
      g_mustPumpOutReceiveQueue = false;
    return;
  }

  int size_of_buffer;
  while (g_RagConnection->RecvPacket(buffer, &size_of_buffer)) {
    short packet_type = g_RagConnection->GetPacketType(buffer);
    switch (packet_type) {
      case HEADER_ZC_NOTIFY_PLAYERCHAT:
        Zc_Notify_Playerchat(buffer);
        break;
      case HEADER_ZC_NPCACK_MAPMOVE:
        Zc_Npcack_Mapmove(buffer);
        break;
      case HEADER_ZC_COUPLESTATUS:
        break;
      case HEADER_ZC_PAR_CHANGE:
        break;
      case HEADER_ZC_ATTACK_RANGE:
        break;
      default:
        LOG(error, "Unknown packet: {:x}", packet_type);
        return;
    };
  }
}

void CGameMode::Zc_Notify_Playerchat(const char *buffer) {
  PACKET_ZC_NOTIFY_PLAYERCHAT *packet = (PACKET_ZC_NOTIFY_PLAYERCHAT *)buffer;
  // CGameMode *v2;      // ebx@1

  LOG(debug, "{}", packet->msg);
  // if (dword_768868) {
  //  g_WindowMgr->SendMsg(5, (int)chat_msg, 30720, 0, 0);
  //} else {
  // g_WindowMgr->SendMsg(1, (int)chat_msg, 65280, 1, 0);
  //  m_world->m_player->SendMsg(
  //      0, 7, chat_msg, 0, 0);
  //}
  // if (dword_7B4480) WriteChat(chat_msg);
}

void CGameMode::Zc_Npcack_Mapmove(const char *buffer) {
  PACKET_ZC_NPCACK_MAPMOVE *packet = (PACKET_ZC_NPCACK_MAPMOVE *)buffer;

  LOG(info, "Moved to map {}", packet->map_name);
}
