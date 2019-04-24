#include "Modes/LoginMode.h"

#ifdef _WIN32
#include <Ws2tcpip.h>
#define inet_ntop InetNtop
#else
#include <arpa/inet.h>
#endif
#include <string.h>

#include "Common/GetTick.h"
#include "Common/Globals.h"
#include "Common/const_strings.h"
#include "Common/debug.h"
#include "Common/service_type.h"
#include "Input/SDLEvents.h"
#include "Network/Packets.h"
#include "UI/UIBmp.h"
#include "UI/UINoticeConfirmWnd.h"
#include "UI/UISelectServerWnd.h"

CLoginMode::CLoginMode(CRagConnection *p_rag_connection,
                       CUIWindowMgr *p_window_mgr)
    : CMode(p_rag_connection, p_window_mgr) {}

void CLoginMode::OnInit(const std::string &mode_name) {
  memset(m_charParam, 5, 6);
  m_charParam[6] = 0;
  m_charParam[7] = 1;
  m_makingCharName[0] = 0;
  m_emailAddress[0] = 0;
  m_wallPaperBmpName = TITLE_FILE;
  m_loop_cond = true;
  m_next_sub_mode = -1;
  // InitNPKCryptFuncTbl();
  m_sub_mode = g_loginStartMode;
  m_sub_mode_cnt = 0;
  OnChangeState(g_loginStartMode);
  g_loginStartMode = 3;
  // g_isStopByLogin = 1;
  // g_Session->InitWithClear();
  // g_guildInfo->Init();
  // g_Session->PreLoadAlwaysNeededRes();
  m_billingInfo.code = 0;
  m_billingInfo.dummy1 = '\0';
  m_billingInfo.time1 = 0;
  m_billingInfo.time2 = 0;
}

int CLoginMode::OnRun() {
  while (GetLoopCond() && !g_sys_quit) {
    if (true /*!dword_7687C8*/) {
      if (m_next_sub_mode != -1) {
        m_sub_mode = m_next_sub_mode;
        m_sub_mode_cnt = 0;
        m_next_sub_mode = -1;
        OnChangeState(m_sub_mode);
      }
    }
    OnUpdate();
    ++m_sub_mode_cnt;
  }
  // RunFadeOut(0);
  return 1;
}

void CLoginMode::OnExit() {}

void *CLoginMode::SendMsg(size_t messageId, const void *val1, const void *val2,
                          const void *val3) {
  void *result = nullptr;

  switch (messageId) {
    case MM_COMMAND: {
      const size_t command_id = reinterpret_cast<size_t>(val1);

      switch (command_id) {
        case 10004:
          m_next_sub_mode = 7;
          break;
        case 10010:
          m_next_sub_mode = 11;
          break;
        case 10001:
          m_next_sub_mode = 8;
          break;
        case 10002:
          m_next_sub_mode = 9;
          break;
        case 10006:
          if (m_sub_mode != 7) {
            break;
          }
          // g_WindowMgr->RemoveAllWindows();
          p_rag_connection_->Disconnect();
          m_next_sub_mode = 6;
          break;
      };
    } break;
    case MM_GOTOIDENTRY:
      g_mustPumpOutReceiveQueue = false;
      m_next_sub_mode = 3;
      break;
    case LMM_CONNECT_TO_ACSVR:
      // TODO(LinkZ): Multiple acc servers
      m_next_sub_mode = 4;
      break;
    case LMM_SENDCHARINFO: {
      const auto p_char_info = reinterpret_cast<const CharacterInfo *>(val1);
      if (p_char_info == nullptr) {
        return nullptr;
      }

      m_new_char_info = *p_char_info;
      m_next_sub_mode = 10;
    } break;
    case LMM_PASSWORD:
      if (val1 != nullptr) {
        strncpy(m_userPassword, reinterpret_cast<const char *>(val1),
                sizeof(m_userPassword));
      }
      break;
    case LMM_ID:
      if (val1 != nullptr) {
        strncpy(m_userId, reinterpret_cast<const char *>(val1),
                sizeof(m_userId));
      }
      break;
    case LMM_GOTOSELECTACCOUNT: {
      const size_t val = reinterpret_cast<size_t>(val2);
      if (val == 135) {
        SendMsg(MM_QUIT);
      } else {
        m_next_sub_mode = 2;
      }
    } break;
    case LMM_SELECTSVR: {
      m_serverSelected = reinterpret_cast<size_t>(val1);
      if (m_serverSelected == -1) {
        break;
      }

      struct in_addr ip;
      ip.s_addr = m_serverInfo[m_serverSelected].ip;
      inet_ntop(AF_INET, &ip, g_charServerAddr.ip, sizeof(g_charServerAddr.ip));
      g_charServerAddr.port = m_serverInfo[m_serverSelected].port;
      m_next_sub_mode = 5;
    } break;
    case MM_QUERYCHARICTORINFO: {
      const size_t char_num = reinterpret_cast<size_t>(val1);
      if (char_num >= m_num_char) {
        return nullptr;
      }

      for (size_t i = 0; i < m_num_char; i++) {
        if (m_charInfo[i].char_slot == char_num) {
          return &m_charInfo[i];
        }
      }
    } break;
    case LMM_SELECT_CHARACTER:
      m_selected_char = reinterpret_cast<size_t>(val1);
      break;
    default:
      return CMode::SendMsg(messageId, val1, val2, val3);
  };

  return result;
}

void CLoginMode::OnUpdate() {
  PollNetworkStatus();

  // Ping the server if necessary
  if ((m_sub_mode == 7 || m_sub_mode == 8 || m_sub_mode == 11 ||
       m_sub_mode == 19) &&
      GetTick() > m_syncRequestTime) {
    PACKET_PING packet;

    m_syncRequestTime = GetTick() + 12000;
    packet.header = HEADER_PING;
    p_rag_connection_->SendPacket(sizeof(packet), (char *)&packet);
  }

  ProcessSDLEvents(p_window_mgr_);
  g_Mouse->ReadState();
  p_window_mgr_->ProcessInput();

  g_Renderer->Clear(true);
  p_window_mgr_->OnProcess();
  p_window_mgr_->RenderWallPaper();
  p_window_mgr_->Render(this);
  if (g_Renderer->DrawScene()) {
    g_Renderer->Flip();
  }
}

void CLoginMode::OnChangeState(int state) {
  p_window_mgr_->RemoveAllWindows();
  m_subModeStartTime = GetTick();
  m_isConnected = 1;

  switch (state) {
    // Notice confirm window
    case 0: {
      const std::string wallpaper_name =
          const_strings::kResourceSubfolder + "login_interface/warning.bmp";
      CUINoticeConfirmWnd *wnd;
      CBitmapRes *bitmap;

      m_wallPaperBmpName = UIBmp(wallpaper_name);
      bitmap =
          static_cast<CBitmapRes *>(g_ResMgr->Get(m_wallPaperBmpName, false));
      p_window_mgr_->SetWallpaper(bitmap);
      wnd = static_cast<CUINoticeConfirmWnd *>(
          p_window_mgr_->MakeWindow(WID_NOTICECONFIRMWND));
      if (wnd) {
        wnd->SendMsg(nullptr, WM_SET_ACTION_BUTTON_OK,
                     (void *)LMM_GOTOSELECTACCOUNT);
      }
    } break;
    case 1:
      break;
    case 2:
      // TODO
      // Account server selection window
      // if (!InitAccountInfo())
      // SendMsg(30, 0, 0, 0);
      m_next_sub_mode = 3;
      break;
    case 3:
      return MakeLoginWindow();
    case 4:
      return ConnectToAccountServer();
    case 5:
      return ConnectToCharServer();
    case 6: {
      // Select char server
      CUISelectServerWnd *wnd;
      char buffer[256];

      wnd = static_cast<CUISelectServerWnd *>(
          p_window_mgr_->MakeWindow(WID_SELECTSERVERWND));
      if (wnd == nullptr) {
        LOG(error, "Cannot create server selection window");
        return;
      }

      wnd->SendMsg(nullptr, WM_SET_ACTION_BUTTON_OK, (void *)LMM_SELECTSVR,
                   nullptr, 0, 0);

      if (m_numServer < 0) {
        wnd->SendMsg(nullptr, 40, 0, 0, 0, 0);
        return;
      }

      for (int i = 0; i < m_numServer; i++) {
        unsigned char *server_name = m_serverInfo[i].name;
        uint16_t nb_of_players = m_serverInfo[i].usercount;

        snprintf(buffer, sizeof(buffer), "%s (%d)", server_name, nb_of_players);
        wnd->AddServer(buffer);
      }
    } break;
    case 7:
      // Select char
      p_window_mgr_->MakeWindow(WID_SELECTCHARWND);
      break;
    case 8:
      // Create char
      p_window_mgr_->MakeWindow(WID_MAKECHARWND);
      break;
    case 9: {
      PACKET_CH_SELECT_CHAR packet = {};
      packet.header = HEADER_CH_SELECT_CHAR;
      packet.char_num = static_cast<uint8_t>(m_selected_char);
      p_rag_connection_->SendPacket(sizeof(packet),
                                    reinterpret_cast<char *>(&packet));
      // v127 = (UIWaitWnd *)UIWindowMgr::MakeWindow(&g_windowMgr, WID_WAITWND);
      // v128 = MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER);
      // UIWaitWnd::SetMsg(v127, v128, 16, 1);
    } break;
    case 10: {
      // Send create char request
      PACKET_CH_MAKE_CHAR packet = {};

      packet.header = HEADER_CH_MAKE_CHAR;
      packet.char_slot = static_cast<uint8_t>(m_selected_char);
      strncpy(packet.name, g_Session->GetCharName(), sizeof(packet.name));
      packet.head_color = m_new_char_info.head_color;
      packet.head_style = m_new_char_info.head_style;

      p_rag_connection_->SendPacket(sizeof(packet),
                                    reinterpret_cast<char *>(&packet));
    } break;
    case 12:
      return ConnectToZoneServer();
    case 13:
      // InitAccountInfo2()
      break;
  };
}

void CLoginMode::MakeLoginWindow() {
  const std::string wallpaper_name =
      const_strings::kResourceSubfolder + "bgi_temp.bmp";
  CUIFrameWnd *login_wnd;

  m_wallPaperBmpName = UIBmp(wallpaper_name);
  auto res =
      static_cast<CBitmapRes *>(g_ResMgr->Get(m_wallPaperBmpName, false));
  p_window_mgr_->SetWallpaper(res);
  login_wnd = p_window_mgr_->MakeWindow(WID_LOGINWND);
  if (!g_hideAccountList && login_wnd != nullptr) {
    login_wnd->SendMsg(nullptr, 88, 0, 0, 0, 0);
  }
}

void CLoginMode::ConnectToAccountServer() {
  ServerAddress server_addr;

  strncpy(server_addr.ip, g_accountAddr, sizeof(server_addr.ip));
  server_addr.port = atoi(g_accountPort);
  LOG(info, "Connecting to the account server ({}:{}) ...", server_addr.ip,
      server_addr.port);
  m_isConnected = p_rag_connection_->Connect(server_addr);
  if (!m_isConnected) {
    LOG(error, "Failed to connect to the account server");
    p_rag_connection_->Disconnect();
    return;
  }

  if (g_bUseCommand) {
    PACKET_CA_CONNECT_INFO_CHANGE packet;
    packet.header = HEADER_CA_CONNECT_INFO_CHANGED;
    memcpy(packet.ID, m_userId, sizeof(packet.ID));
    p_rag_connection_->SendPacket(sizeof(packet),
                                  reinterpret_cast<char *>(&packet));
  }

  CheckExeHashFromAccServer();
  if (g_passwordEncrypt) {
    PACKET_CA_REQ_HASH packet;
    packet.header = HEADER_CA_REQ_HASH;
    p_rag_connection_->SendPacket(sizeof(packet),
                                  reinterpret_cast<char *>(&packet));
    // m_wndWait->SetMsg(g_MsgStrMgr->GetMsgStr(MSI_WAITING_RESPONSE_FROM_SERVER),
    // 16, 1);
    return;
  }

  // if (g_serviceType != ServiceType::kKorea) {
  PACKET_CA_LOGIN packet;
  packet.header = HEADER_CA_LOGIN;
  packet.version = g_version;
  strncpy(packet.username, m_userId, sizeof(packet.username));
  strncpy(packet.password, m_userPassword, sizeof(packet.password));
  LOG(debug, "login: '{}', pass: '{}'", m_userId, m_userPassword);
  packet.client_type = g_clientType;  // GetAccountType();
  p_rag_connection_->SendPacket(sizeof(packet), (char *)&packet);
  //} else {
  //  PACKET_CA_LOGIN_CHANNEL packet;
  //  packet.header = HEADER_CA_LOGIN_CHANNEL;
  //  packet.version = g_version;
  //  strncpy(packet.username, m_userId, sizeof(packet.username));
  //  strncpy(packet.password, m_userPassword, sizeof(packet.password));
  //  strcpy(packet.ip_address, "111.111.111.111");
  //  memset(packet.mac_address, 0x11, sizeof(packet.mac_address));
  //  packet.clienttype = g_clientType;
  //  packet.channeling_corp = g_isGravityID;
  //  p_rag_connection_->SendPacket(sizeof(packet), (char *)&packet);
  //}

  // CUIWaitWnd *waitwnd =
  //    (CUIWaitWnd *)g_WindowMgr->MakeWindow(WID_WAITWND);
  // waitwnd->SetMsg(g_MsgStrMgr->GetMsgStr(MSI_WAITING_RESPONSE_FROM_SERVER),
  // 16, 1);
}

void CLoginMode::ConnectToCharServer() {
  p_rag_connection_->Disconnect();

  LOG(info, "Connecting to the char server ({}:{}) ...", g_charServerAddr.ip,
      g_charServerAddr.port);
  m_isConnected = p_rag_connection_->Connect(g_charServerAddr);
  // WinMainNpKeyStopEncryption();
  if (!m_isConnected) {
    LOG(error, "Failed to connect to the char server");
    p_rag_connection_->Disconnect();
    const auto error_msg = g_MsgStrMgr->GetMsgStr(MSI_SERVER_CONNECTION_FAILED);
    if (p_window_mgr_->ErrorMsg(error_msg, 1, 1, 1, 0) != 203) {
      g_mustPumpOutReceiveQueue = 0;
    }

    m_next_sub_mode = 3;
    return;
  }

  PACKET_CH_ENTER packet;
  packet.header = HEADER_CH_ENTER;
  packet.client_type = g_clientType;
  packet.auth_code = m_authCode;
  packet.account_id = m_account_id;
  packet.user_level = m_userLevel;
  packet.Sex = g_Session->GetSex();
  g_mustPumpOutReceiveQueue = true;
  p_rag_connection_->SendPacket(sizeof(packet),
                                reinterpret_cast<char *>(&packet));
}

void CLoginMode::ConnectToZoneServer() {
  LOG(info, "Connecting to the zone server ({}:{}) ...", g_zoneServerAddr.ip,
      g_zoneServerAddr.port);
  m_isConnected = p_rag_connection_->Connect(g_zoneServerAddr);
  if (!m_isConnected) {
    LOG(error, "Failed to connect to the zone server");
    p_rag_connection_->Disconnect();
    const auto error_msg = g_MsgStrMgr->GetMsgStr(MSI_SERVER_CONNECTION_FAILED);
    if (p_window_mgr_->ErrorMsg(error_msg, 1, 1, 1, 0) != 203) {
      g_mustPumpOutReceiveQueue = 0;
    }

    m_next_sub_mode = 3;
    return;
  }

  PACKET_CZ_ENTER2 packet;
  packet.header = HEADER_CZ_ENTER2;
  packet.client_time = GetTick();
  packet.auth_code = m_authCode;
  packet.gid = m_char_id;
  packet.aid = m_account_id;
  packet.sex = g_Session->GetSex();

  p_rag_connection_->SendPacket(sizeof(packet),
                                reinterpret_cast<char *>(&packet));
  p_rag_connection_->SetBlock(true);
  // wnd = (UIWaitWnd *)UIWindowMgr::MakeWindow(&g_windowMgr,
  // WID_WAITWND);  str = MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER);
  // wnd->SetMsg(str, 16, 1);
}

void CLoginMode::PollNetworkStatus() {
  char buffer[2048];

  if (!p_rag_connection_->Poll()) {
    SendMsg(1, 0, 0, 0);
  }

  if (g_mustPumpOutReceiveQueue) {
    uint32_t aid;
    if (p_rag_connection_->Recv(reinterpret_cast<char *>(&aid), sizeof(aid),
                                1)) {
      g_mustPumpOutReceiveQueue = false;
    }
    return;
  }

  int size_of_buffer;
  while (p_rag_connection_->RecvPacket(buffer, &size_of_buffer)) {
    const int16_t packet_type = p_rag_connection_->GetPacketType(buffer);
    switch (packet_type) {
      case HEADER_AC_ACCEPT_LOGIN:
        Ac_Accept_Login(buffer);
        break;
      case HEADER_AC_REFUSE_LOGIN:
        Ac_Refuse_Login(buffer);
        break;
      case HEADER_AC_REFUSE_LOGIN_R2:
        LOG(debug, "AC_REFUSE_LOGIN_R2");
        break;
      case HEADER_HC_ACCEPT_ENTER2:
        LOG(debug, "HC_ACCEPT_ENTER2");
        break;
      case HEADER_HC_CHARLIST_NOTIFY:
        LOG(debug, "HC_CHARLIST_NOTIFY");
        break;
      case HEADER_HC_ACCEPT_ENTER:
        Hc_Accept_Enter(buffer);
        break;
      case HEADER_HC_REFUSE_ENTER:
        Hc_Refuse_Enter(buffer);
        break;
      case HEADER_HC_SECOND_PASSWD_LOGIN:
        LOG(debug, "HC_SECOND_PASSWD_LOGIN");
        break;
      case HEADER_HC_ACCEPT_MAKECHAR:
        Hc_Accept_Makechar(buffer);
        break;
      case HEADER_HC_REFUSE_MAKECHAR:
        Hc_Refuse_Makechar(buffer);
        break;
      case HEADER_HC_ACCEPT_DELETECHAR:
        Hc_Accept_Deletechar(buffer);
        break;
      case HEADER_HC_REFUSE_DELETECHAR:
        Hc_Refuse_Deletechar(buffer);
        break;
      case HEADER_HC_NOTIFY_ZONESVR:
        Hc_Notify_Zonesvr(buffer);
        break;
      case HEADER_ZC_ACCEPT_ENTER:
        Zc_Accept_Enter(buffer);
        break;
      case HEADER_ZC_ACCEPT_ENTER2:
        Zc_Accept_Enter2(buffer);
        break;
      case HEADER_ZC_REFUSE_ENTER:
        Zc_Refuse_Enter(buffer);
        break;
      case HEADER_SC_NOTIFY_BAN:
        LOG(debug, "SC_NOTIFY_BAN");
        // Sc_Notify_Ban(buffer);
        return;
      case HEADER_AC_EVENT_RESULT:
        LOG(debug, "AC_EVENT_RESULT");
        break;
      case HEADER_HC_BLOCK_CHARACTER:
        LOG(debug, "HC_BLOCK_CHARACTER");
        break;
      case HEADER_SC_BILLING_INFO:
        LOG(debug, "SC_BILLING_INFO");
        break;
      case HEADER_AC_ASK_PNGAMEROOM:
        LOG(debug, "AC_ASK_PNGAMEROOM");
        break;
      case HEADER_SC_ACK_ENCRYPTION:
        LOG(debug, "SC_ACK_ENCRYPTION");
        break;
      case HEADER_AC_ACK_HASH:
        LOG(debug, "AC_ACK_HASH");
        break;
      case HEADER_AC_NOTIFY_ERROR:
        LOG(debug, "AC_NOTIFY_ERROR");
        break;
      case HEADER_PING:
        LOG(debug, "PING");
        // Do nothing
        break;
      case HEADER_HC_CHARNOTBEENSELECTED:
        LOG(debug, "HC_CHARNOTBEENSELECTED");
        break;
      case HEADER_HC_ACK_IS_VALID_CHARNAME:
        LOG(debug, "HC_ACK_IS_VALID_CHARNAME");
        break;
      case HEADER_HC_ACK_CHANGE_CHARNAME:
        LOG(debug, "HC_ACK_CHANGE_CHARNAME");
        break;
      case HEADER_HC_REFUSE_SELECTCHAR:
        LOG(debug, "HC_REFUSE_SELECTCHAR");
        break;
      default:
        LOG(error, "Received unknown packet 0x{:x}", packet_type);
        return;
    };
  }
  // ResetQueue
}

void CLoginMode::Ac_Accept_Login(const char *buffer) {
  auto packet = reinterpret_cast<const PACKET_AC_ACCEPT_LOGIN *>(buffer);
  char sex;

  m_authCode = packet->auth_code;
  m_account_id = packet->account_id;
  m_userLevel = packet->user_level;

  if (packet->sex < 10) {
    sex = packet->sex;
  } else {
    sex = packet->sex - 10;
  }

  g_Session->SetSex(sex);
  // g_Session->SetTextType(false, false);
  m_numServer = (packet->packet_len - sizeof(PACKET_AC_ACCEPT_LOGIN)) /
                sizeof(CharServerInfo);
  memcpy(m_serverInfo, &(packet->server_info),
         m_numServer * sizeof(CharServerInfo));
  p_rag_connection_->Disconnect();
  g_passwordWrong = false;
  m_next_sub_mode = 6;
}

void CLoginMode::Ac_Refuse_Login(const char *buffer) {
  auto packet = reinterpret_cast<const PACKET_AC_REFUSE_LOGIN *>(buffer);
  std::string msg;

  if (packet->error_code != 18) {
    p_rag_connection_->Disconnect();
  }

  switch (packet->error_code) {
    case 0:
      msg = g_MsgStrMgr->GetMsgStr(MSI_INCORRECT_USERID);
      break;
    case 1:
      msg = g_MsgStrMgr->GetMsgStr(MSI_INCORRECT_LOGIN_PASSWORD);
      break;
    case 3:
      msg = g_MsgStrMgr->GetMsgStr(MSI_INVALID_VERSION);
      break;
    case 5:
      msg = g_MsgStrMgr->GetMsgStr(MSI_INVALID_VERSION);
      SendMsg(MM_QUIT);
      break;
    default:
      msg = g_MsgStrMgr->GetMsgStr(MSI_ACCESS_DENIED);
  };
  p_window_mgr_->ErrorMsg(msg, 0, 1, 0, 0);
}

void CLoginMode::CheckExeHashFromAccServer() {}

void CLoginMode::Hc_Accept_Enter(const char *buffer) {
  auto packet = reinterpret_cast<const PACKET_HC_ACCEPT_ENTER *>(buffer);

  /*memcpy(&m_billingInfo, 0, sizeof(m_billingInfo));
  m_billingInfo.code = ntohl(m_billingInfo.code);
  m_billingInfo.time1 = ntohl(m_billingInfo.time1);
  m_billingInfo.time2 = ntohl(m_billingInfo.time2);*/
  LOG(debug, "HC_ACCEPT len: {}", packet->packet_len);
  m_num_char = (packet->packet_len - sizeof(PACKET_HC_ACCEPT_ENTER)) /
               sizeof(CharacterInfo);
  memcpy(m_charInfo, packet->charinfo, m_num_char * sizeof(CharacterInfo));
  m_next_sub_mode = 7;
}

void CLoginMode::Hc_Refuse_Enter(const char *buffer) {
  auto packet = reinterpret_cast<const PACKET_HC_REFUSE_ENTER *>(buffer);
  std::string msg;
  int change_msg;

  p_rag_connection_->Disconnect();
  if (packet->error_code == 1) {
    change_msg = 1;
    msg = g_MsgStrMgr->GetMsgStr(MSI_ID_MISMATCH);
  } else {
    change_msg = 0;
    msg = g_MsgStrMgr->GetMsgStr(MSI_ACCESS_DENIED);
  }
  p_window_mgr_->ErrorMsg(msg, 0, 1, change_msg, 0);
}

void CLoginMode::Hc_Accept_Makechar(const char *buffer) {
  auto packet = reinterpret_cast<const PACKET_HC_ACCEPT_MAKECHAR *>(buffer);

  memcpy(&m_charInfo[m_num_char], &packet->charinfo,
         sizeof(m_charInfo[m_num_char]));
  m_next_sub_mode = 7;
  m_num_char++;
}

void CLoginMode::Hc_Refuse_Makechar(const char *buffer) {
  auto packet = reinterpret_cast<const PACKET_HC_REFUSE_MAKECHAR *>(buffer);
  const std::string error_msg = [error = packet->error_code]() {
    switch (error) {
      case 0:
        return g_MsgStrMgr->GetMsgStr(MSI_CHARACTER_NAME_ALREADY_EXISTS);
      case 1:
        return g_MsgStrMgr->GetMsgStr(MSI_LIMIT_AGE);
      case 2:
        return g_MsgStrMgr->GetMsgStr(MSI_LIMIT_CHAR_DELETE);
      case 3:
        return g_MsgStrMgr->GetMsgStr(MSI_FR_ERR_MKCHAR_INVALID_SLOT);
      case 11:
        return g_MsgStrMgr->GetMsgStr(MSI_NEED_PREMIUM_SERVICE);
      default:
        return g_MsgStrMgr->GetMsgStr(MSI_CHARACTER_CREATION_DENIED);
    };
  }();

  p_window_mgr_->ErrorMsg(error_msg, 0, 1, 0, 0);
  m_next_sub_mode = 7;
}

void CLoginMode::Hc_Accept_Deletechar(const char * /*buffer*/) {
  if (m_num_char == 0) {
    return;
  }

  CharacterInfo tmp_char_infos[0xC] = {};
  auto char_index = m_num_char;
  unsigned int i = 0;
  unsigned int j = 0;

  // Remove deleted char's info from m_charInfo
  while (char_index) {
    if (m_charInfo->char_slot != m_selected_char) {
      memcpy(&tmp_char_infos[i++], &m_charInfo[j], sizeof(tmp_char_infos[0]));
    }

    j++;
    char_index--;
  }

  const auto data_size =
      std::min(sizeof(m_charInfo), --m_num_char * sizeof(m_charInfo[0]));
  memcpy(&m_charInfo, &tmp_char_infos, data_size);
  m_next_sub_mode = 7;
}

void CLoginMode::Hc_Refuse_Deletechar(const char *buffer) {
  auto packet = reinterpret_cast<const PACKET_HC_REFUSE_DELETECHAR *>(buffer);
  const std::string error_msg = [error = packet->error_code]() {
    if (error != 0) {
      if (error == 1) {
        return g_MsgStrMgr->GetMsgStr(MSI_FR_ERR_DELCHAR_INVALID_SLOT);
      }
      return g_MsgStrMgr->GetMsgStr(MSI_CANNOT_DELETE_CHARACTER);
    }

    if (g_serviceType != ServiceType::kKorea) {
      return g_MsgStrMgr->GetMsgStr(MSI_CANNOT_DELETE_CHARACTER_EMAIL);
    }

    return g_MsgStrMgr->GetMsgStr(
        MSI_CANNOT_DELETE_CHARACTER_PEOPLE_REG_NUMBER);
  }();

  p_window_mgr_->ErrorMsg(error_msg, 0, 1, 0, 0);
  m_next_sub_mode = 7;
}

void CLoginMode::Zc_Accept_Enter(const char *buffer) {
  auto packet = reinterpret_cast<const PACKET_ZC_ACCEPT_ENTER *>(buffer);
  g_Session->SetServerTime(packet->startTime);
  g_Session->SetPlayerPosDir(
      (packet->PosDir[1] >> 6) | 4 * packet->PosDir[0],
      (packet->PosDir[2] >> 4) | 16 * (packet->PosDir[1] & 0x3F),
      packet->PosDir[2] & 0xF);

  LOG(info, "Entering zone server. The current map is {}", m_current_map);
  g_ModeMgr->Switch(ModeType::kGame, m_current_map);
  p_rag_connection_->SetBlock(false);
  // wnd = (UIWaitWnd *)g_WindowMgr->MakeWindow(WID_WAITWND);
  // str = MsgStr(MSI_PLEASE_BE_PATIENT);
  // wnd->SetMsg(str, 17, 1);
}

void CLoginMode::Zc_Accept_Enter2(const char *buffer) {
  Zc_Accept_Enter(buffer);
}

void CLoginMode::Hc_Notify_Zonesvr(const char *buffer) {
  auto packet = reinterpret_cast<const PACKET_HC_NOTIFY_ZONESVR *>(buffer);
  in_addr ip;

  m_char_id = packet->char_id;
  const std::string gat_name = reinterpret_cast<const char *>(packet->map_name);
  m_current_map = gat_name.substr(0, gat_name.length() - 4) + ".rsw";

  ip.s_addr = packet->addr.ip;
  inet_ntop(AF_INET, &ip, g_zoneServerAddr.ip, sizeof(g_zoneServerAddr.ip));
  g_zoneServerAddr.port = packet->addr.port;
  p_rag_connection_->Disconnect();
  m_next_sub_mode = 12;
}

void CLoginMode::Zc_Refuse_Enter(const char *buffer) {
  auto packet = reinterpret_cast<const PACKET_ZC_REFUSE_ENTER *>(buffer);
  const std::string error_msg = [error = packet->error]() {
    switch (error) {
      case 0:
        return g_MsgStrMgr->GetMsgStr(MSI_CLIENTTYPEMISMATCH);
      case 1:
        return g_MsgStrMgr->GetMsgStr(MSI_ID_MISMATCH);
      default:
        return g_MsgStrMgr->GetMsgStr(MSI_ACCESS_DENIED);
    };
  }();

  p_window_mgr_->ErrorMsg(error_msg, 0, 1, 0, 0);
  p_rag_connection_->Disconnect();
  m_next_sub_mode = 3;
}
