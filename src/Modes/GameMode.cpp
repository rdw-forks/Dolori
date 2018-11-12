#include "Modes/GameMode.h"

#define GLM_ENABLE_EXPERIMENTAL

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

CGameMode::CGameMode(CRagConnection *p_rag_connection,
                     CUIWindowMgr *p_window_mgr)
    : CMode(p_rag_connection, p_window_mgr),
      m_world(),
      m_view(),
      m_noMove(0),
      m_isOnQuest(0),
      m_isPlayerDead(0),
      // m_nameBalloon(nullptr),
      // m_targetNameBalloon(nullptr),
      // m_broadcastBalloon(nullptr),
      // m_skillNameBalloon(nullptr),
      // m_skillMsgBalloon(nullptr),
      // m_skillUsedMsgBalloon(nullptr),
      // m_playerGage(nullptr),
      m_nameActorAid(0),
      m_nameBalloonWidth(0),
      m_nameBalloonHeight(0),
      m_nameDisplayed(1),
      m_nameDisplayed2(1),
      m_waitingUseItemAck(0),
      m_waitingItemThrowAck(0),
      m_waitingReqStatusAck(0),
      // m_dragInfo.m_dragType(0),
      // m_dragInfo.m_dragItemIndex(0),
      // m_dragInfo.m_numDragItem(0),
      // m_dragInfo.m_slotNum(-1),
      // m_dragInfo.m_isIdentified(0),
      m_lastNaid(0),
      m_menuTargetAID(0),
      m_lastPcGid(0),
      m_lastMonGid(0),
      m_lastLockOnMonGid(0),
      m_isAutoMoveClickOn(1),
      m_isWaitingWhisperSetting(0),
      m_isWaitingEnterRoom(0),
      m_isWaitingAddExchangeItem(0),
      m_waitingWearEquipAck(GetTick() - 2000),
      m_isWaitingCancelExchangeItem(0),
      m_waitingTakeoffEquipAck(GetTick() - 2000),
      m_isReqUpgradeSkillLevel(0),
      m_exchangeItemCnt(0),
      m_sameChatRepeatCnt(0),
      m_numNotifyTime(0) {}

void CGameMode::Intialize() {
  // g_SnapMgr->RemoveAll();
  // p_window_mgr_->RemoveAllWindowsExceptChatWnd();
  p_window_mgr_->SetWallpaper(nullptr);
  p_window_mgr_->MakeWindow(WID_BASICINFOWND);
  p_window_mgr_->MakeWindow(WID_CHATWND);
}

void CGameMode::OnInit(const std::string &mode_name) {
  m_posOfBossMon.x = -1;
  m_posOfBossMon.y = -1;
  m_isBossAlarm = 0;
  m_onCopyName = 0;
  m_rsw_name = mode_name;

  g_Renderer->Clear(true);
  p_window_mgr_->SetWallpaper(nullptr);
  // p_window_mgr_->RemoveAllWindowsExceptChatWnd();
  // p_window_mgr_->HideChatWnd();
  // p_window_mgr_->MakeWindow(WID_LOADINGWND);
  p_window_mgr_->RenderWallPaper();
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
  while (GetLoopCond() && !g_sys_quit) {
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
  PollNetworkStatus();

  // m_scheduler->OnRun()
  // ProcessDamageSituation()

  g_Renderer->Clear(false);
  g_Renderer->ClearBackground();
  if (GetLoopCond()) {
    ProcessInput();
    // m_world->ProcessActors();
    m_view.OnCalcViewInfo(m_world.GetPlayer().GetPos());
  }

  m_view.OnRender();
  m_world.Render();
  // p_window_mgr_->RenderMenu();
  p_window_mgr_->Render(this);
  // DrawDragImage();
  // DrawMouseCursor();
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
  // switch (msg) {
  //  default:
  //    return nullptr;
  //};

  return nullptr;
}

void CGameMode::ProcessInput() {
  ProcessSDLEvents();
  g_Mouse->ReadState();
  int process_type = p_window_mgr_->ProcessInput();
  p_window_mgr_->OnProcess();
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
  const float kSensitivity = 0.8f;

  if (button_state == CMouse::ButtonState::kDown) {
    // m_rBtnClickX = g_Mouse->GetXPos();
    // m_rBtnClickY = g_Mouse->GetYPos();
    m_view.AddLongitude((g_Mouse->GetYPos() - m_oldMouseY) * kSensitivity);
    m_view.AddLatitude(-(g_Mouse->GetXPos() - m_oldMouseX) * kSensitivity);
  } else {
  }
}

void CGameMode::ProcessMouseWheel(int process_type) {
  const float kSensitivity = 10.f;

  m_view.AddDistance(g_Mouse->GetWheel() * kSensitivity);
}
void CGameMode::PollNetworkStatus() {
  char buffer[2048];

  if (!p_rag_connection_->Poll()) {
    SendMsg(1);
  }

  if (g_mustPumpOutReceiveQueue) {
    uint32_t aid;
    if (p_rag_connection_->Recv(reinterpret_cast<char *>(&aid), sizeof(aid),
                                1) > 0) {
      g_mustPumpOutReceiveQueue = false;
    }

    return;
  }

  int size_of_buffer;
  while (p_rag_connection_->RecvPacket(buffer, &size_of_buffer)) {
    int16_t packet_type = p_rag_connection_->GetPacketType(buffer);
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
  auto packet = reinterpret_cast<const PACKET_ZC_NOTIFY_PLAYERCHAT *>(buffer);

  LOG(debug, "{}", packet->msg);
  // if (dword_768868) {
  // p_window_mgr_->SendMsg(5, reinterpret_cast<const void *>(packet->msg),
  //                       reinterpret_cast<const void *>(30720));
  //} else {
  p_window_mgr_->SendMsg(1, reinterpret_cast<const void *>(packet->msg),
                         reinterpret_cast<const void *>(0x00ff00),
                         reinterpret_cast<const void *>(1));
  // m_world.GetPlayer().SendMsg(0, 7, chat_msg, 0, 0);
  //}
  // if (dword_7B4480) WriteChat(chat_msg);
}

void CGameMode::Zc_Npcack_Mapmove(const char *buffer) {
  auto packet = reinterpret_cast<const PACKET_ZC_NPCACK_MAPMOVE *>(buffer);

  LOG(info, "Moved to map {}", packet->map_name);
}

const std::string &CGameMode::rsw_name() const { return m_rsw_name; }
