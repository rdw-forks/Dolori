#include "Modes/GameMode.h"

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

  PACKET_CZ_NOTIFY_ACTORINIT actor_init;
  actor_init.header = HEADER_CZ_NOTIFY_ACTORINIT;
  p_rag_connection_->SendPacket(sizeof(actor_init),
                                reinterpret_cast<char *>(&actor_init));

  PACKET_CZ_REQUEST_TIME req_time;
  req_time.header = HEADER_CZ_REQUEST_TIME2;
  req_time.client_time = GetTick();
  p_rag_connection_->SendPacket(sizeof(req_time),
                                reinterpret_cast<char *>(&req_time));
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
  }
}

void *CGameMode::SendMsg(size_t msg, const void *val1, const void *val2,
                         const void *val3) {
  switch (msg) {
    case MM_CHATMSG: {
      // TODO(LinkZ): Add the following optional checks
      // g_Session->IsEFST_Berserk()
      // InsultFilter::IsBadSentence()
      // IsSameSentence(repeat_count)
      const auto chat_buffer = reinterpret_cast<const char *>(val1);
      std::string message = g_Session->GetCharName();
      message += " : ";
      // g_Language->GetLanguageCharset(false)
      message += chat_buffer;

      const uint16_t packet_size =
          sizeof(PACKET_CZ_REQUEST_CHAT) + message.length() + 1;
      auto p_packet =
          reinterpret_cast<PACKET_CZ_REQUEST_CHAT *>(new uint8_t[packet_size]);
      p_packet->header = HEADER_CZ_REQUEST_CHAT;
      p_packet->packet_length = packet_size;
      ::strncpy(p_packet->msg, message.c_str(), message.length() + 1);
      p_rag_connection_->SendPacket(p_packet->packet_length,
                                    reinterpret_cast<char *>(p_packet));
      delete[] p_packet;
    } break;
    case MM_WHISPERMSG:
      break;
    case MM_PROCESS_TALK_TYPE: {
      const auto talk_type = reinterpret_cast<size_t>(val1);
      const auto chat_buffer = reinterpret_cast<const char *>(val2);
      ProcessTalkType(talk_type, chat_buffer);
    } break;
    default:
      LOG(error, "Unknown message id for GameMode: {}", msg);
      break;
  }

  return nullptr;
}

void CGameMode::ProcessInput() {
  ProcessSDLEvents(p_window_mgr_);
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
    const int16_t packet_type = p_rag_connection_->GetPacketType(buffer);
    switch (packet_type) {
      case HEADER_ZC_NOTIFY_PLAYERCHAT:
        Zc_Notify_Playerchat(buffer);
        break;
      case HEADER_ZC_NPCACK_MAPMOVE:
        Zc_Npcack_Mapmove(buffer);
        break;
      case HEADER_ZC_SAY_DIALOG:
        // Displays an NPC dialog message
        LOG(debug, "ZC_SAY_DIALOG");
        break;
      case HEADER_ZC_WAIT_DIALOG:
        // Adds a 'next' button to an NPC dialog
        LOG(debug, "ZC_WAIT_DIALOG");
        break;
      case HEADER_ZC_CLOSE_DIALOG:
        // Adds a 'close' button to an NPC dialog
        LOG(debug, "ZC_CLOSE_DIALOG");
        break;
      case HEADER_ZC_COUPLESTATUS:
        LOG(debug, "ZC_COUPLESTATUS");
        break;
      case HEADER_ZC_PAR_CHANGE:
        LOG(debug, "ZC_PAR_CHANGE");
        break;
      case HEADER_ZC_ATTACK_RANGE:
        LOG(debug, "ZC_PAR_CHANGE");
        break;
      case HEADER_ZC_SPRITE_CHANGE2:
        LOG(debug, "ZC_SPRITE_CHANGE2");
        break;
      case HEADER_ZC_EQUIPMENT_ITEMLIST3:
        LOG(debug, "ZC_EQUIPMENT_ITEMLIST3");
        break;
      case HEADER_ZC_INVENTORY_ITEMLIST_EQUIP_V5:
        LOG(debug, "ZC_INVENTORY_ITEMLIST_EQUIP_V5");
        break;
      case HEADER_ZC_NOTIFY_MAPPROPERTY:
        LOG(debug, "ZC_NOTIFY_MAPPROPERTY");
        break;
      case HEADER_ZC_MAPPROPERTY_R2:
        LOG(debug, "ZC_MAPPROPERTY_R2");
        break;
      case HEADER_ZC_NOTIFY_STANDENTRY:
        LOG(debug, "ZC_NOTIFY_STANDENTRY");
        break;
      case HEADER_ZC_NOTIFY_STANDENTRY8:
        LOG(debug, "ZC_NOTIFY_STANDENTRY8");
        break;
      case HEADER_ZC_SKILLINFO_LIST:
        LOG(debug, "ZC_SKILLINFO_LIST");
        break;
      case HEADER_ZC_SHORTCUT_KEY_LIST:
        LOG(debug, "ZC_SHORTCUT_KEY_LIST");
        break;
      case HEADER_ZC_SHORTCUT_KEY_LIST_V2:
        LOG(debug, "ZC_SHORTCUT_KEY_LIST_V2");
        break;
      case HEADER_ZC_LONGPAR_CHANGE:
        LOG(debug, "ZC_LONGPAR_CHANGE");
        break;
      case HEADER_ZC_STATUS:
        LOG(debug, "ZC_STATUS");
        break;
      case HEADER_ZC_PARTY_CONFIG:
        LOG(debug, "ZC_PARTY_CONFIG");
        break;
      case HEADER_ZC_CONFIG_NOTIFY:
        LOG(debug, "ZC_CONFIG_NOTIFY");
        break;
      case HEADER_ZC_BROADCAST2:
        Zc_Broadcast2(buffer);
        LOG(debug, "ZC_BROADCAST2");
        break;
      case HEADER_ZC_EMOTION:
        LOG(debug, "ZC_EMOTION");
        break;
      case HEADER_ZC_NAVIGATION_ACTIVE:
        LOG(debug, "ZC_NAVIGATION_ACTIVE");
        break;
      case HEADER_ZC_QUEST_NOTIFY_EFFECT:
        LOG(debug, "ZC_QUEST_NOTIFY_EFFECT");
        break;
      case HEADER_ZC_NOTIFY_TIME:
        LOG(debug, "ZC_NOTIFY_TIME");
        break;
      default:
        LOG(error, "Unknown packet: {:x}", packet_type);
        return;
    };
  }
}

const std::string &CGameMode::rsw_name() const { return m_rsw_name; }

void CGameMode::Zc_Notify_Playerchat(const void *buffer) {
  const auto packet = static_cast<const PACKET_ZC_NOTIFY_PLAYERCHAT *>(buffer);

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

void CGameMode::Zc_Npcack_Mapmove(const void *buffer) {
  const auto packet = static_cast<const PACKET_ZC_NPCACK_MAPMOVE *>(buffer);

  LOG(info, "Moved to map {}", packet->map_name);
}

void CGameMode::Zc_Broadcast2(const void *buffer) {
  const auto packet = static_cast<const PACKET_ZC_BROADCAST2 *>(buffer);

  p_window_mgr_->SendMsg(1, reinterpret_cast<const void *>(packet->msg),
                         reinterpret_cast<const void *>(packet->font_color),
                         reinterpret_cast<const void *>(1));
}
