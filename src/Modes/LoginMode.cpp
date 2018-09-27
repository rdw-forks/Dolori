#include "Modes/LoginMode.h"

#ifdef WIN32
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

CLoginMode::CLoginMode() : CMode() {}

void CLoginMode::OnInit(const char *mode_name) {
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
  while (m_loop_cond && !g_sys_quit) {
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
      size_t command_id = reinterpret_cast<size_t>(val1);

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
          g_RagConnection->Disconnect();
          m_next_sub_mode = 6;
          break;
      };
    } break;
    case MM_GOTOIDENTRY:
      g_mustPumpOutReceiveQueue = false;
      m_next_sub_mode = 3;
      break;
    case LMM_CONNECT_TO_ACSVR:
      // TODO: Multiple acc servers
      m_next_sub_mode = 4;
      break;
    case LMM_SENDCHARINFO:
      m_next_sub_mode = 10;
      break;
    case LMM_PASSWORD:
      if (val1) {
        strncpy(m_userPassword, (char *)val1, sizeof(m_userPassword));
      }
      break;
    case LMM_ID:
      if (val1) {
        strncpy(m_userId, (char *)val1, sizeof(m_userId));
      }
      break;
    case LMM_GOTOSELECTACCOUNT: {
      size_t val = (size_t)val2;
      if (val == 135) {
        g_ModeMgr->GetCurMode()->SendMsg(MM_QUIT, 0, 0, 0);
      } else {
        m_next_sub_mode = 2;
      }
    } break;
    case LMM_SELECTSVR: {
      m_serverSelected = (size_t)val1;
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
      size_t char_num = (size_t)val1;
      if (m_num_char <= 0 || char_num >= m_num_char) {
        return nullptr;
      }

      for (int i = 0; i < m_num_char; i++) {
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
    struct PACKET_PING packet;
    int packet_size;

    m_syncRequestTime = GetTick() + 12000;
    packet.header = HEADER_PING;
    packet_size = g_RagConnection->GetPacketSize(HEADER_PING);
    g_RagConnection->SendPacket(packet_size, (char *)&packet);
  }

  ProcessSDLEvents();
  g_Mouse->ReadState();
  g_WindowMgr->ProcessInput();

  g_Renderer->Clear(true);
  g_WindowMgr->RenderWallPaper();
  g_WindowMgr->Render(this);
  if (g_Renderer->DrawScene()) {
    g_Renderer->Flip();
  }
}

void CLoginMode::OnChangeState(int state) {
  g_WindowMgr->RemoveAllWindows();
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
      g_WindowMgr->SetWallpaper(bitmap);
      wnd = static_cast<CUINoticeConfirmWnd *>(
          g_WindowMgr->MakeWindow(WID_NOTICECONFIRMWND));
      if (wnd) {
        wnd->SendMsg(nullptr, WM_SET_ACTION_BUTTON_OK,
                     (void *)LMM_GOTOSELECTACCOUNT, 0, 0, 0);
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
          g_WindowMgr->MakeWindow(WID_SELECTSERVERWND));
      if (wnd) {
        wnd->SendMsg(nullptr, WM_SET_ACTION_BUTTON_OK, (void *)LMM_SELECTSVR,
                     nullptr, 0, 0);
      }

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
      g_WindowMgr->MakeWindow(WID_SELECTCHARWND);
      break;
    case 8:
      // Create char
      g_WindowMgr->MakeWindow(WID_MAKECHARWND);
      break;
    case 9: {
      PACKET_CH_SELECT_CHAR packet = {};

      packet.header = HEADER_CH_SELECT_CHAR;
      packet.char_num = m_selected_char;
      const int packet_size =
          g_RagConnection->GetPacketSize(HEADER_CH_SELECT_CHAR);
      g_RagConnection->SendPacket(packet_size,
                                  reinterpret_cast<char *>(&packet));
      // v127 = (UIWaitWnd *)UIWindowMgr::MakeWindow(&g_windowMgr, WID_WAITWND);
      // v128 = MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER);
      // UIWaitWnd::SetMsg(v127, v128, 16, 1);
    } break;
    case 10: {
      // Send create char request
      PACKET_CH_MAKE_CHAR packet = {};

      packet.header = HEADER_CH_MAKE_CHAR;
      packet.char_slot = m_selected_char;
      strncpy(packet.name, g_Session->GetCharName(), sizeof(packet.name));
      // TODO: replace with actual values
      packet.head_color = 1;
      packet.head_style = 1;
      packet.str = 5;
      packet.agi = 5;
      packet.vit = 5;
      packet.int_ = 5;
      packet.dex = 5;
      packet.luk = 5;

      const int packet_size =
          g_RagConnection->GetPacketSize(HEADER_CH_MAKE_CHAR);
      g_RagConnection->SendPacket(packet_size,
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
  g_WindowMgr->SetWallpaper(res);
  login_wnd = g_WindowMgr->MakeWindow(WID_LOGINWND);
  if (!g_hideAccountList && login_wnd) {
    login_wnd->SendMsg(nullptr, 88, 0, 0, 0, 0);
  }
}

void CLoginMode::ConnectToAccountServer() {
  SERVER_ADDRESS server_addr;

  strncpy(server_addr.ip, g_accountAddr, sizeof(server_addr.ip));
  server_addr.port = atoi(g_accountPort);
  LOG(info, "Connecting to the account server ({}:{}) ...", server_addr.ip,
      server_addr.port);
  m_isConnected = g_RagConnection->Connect(&server_addr);
  if (!m_isConnected) {
    LOG(error, "Failed to connect to the account server");
    g_RagConnection->Disconnect();
    return;
  }

  if (g_bUseCommand) {
    struct PACKET_CA_CONNECT_INFO_CHANGE packet;
    int packet_size;

    packet.PacketType = HEADER_CA_CONNECT_INFO_CHANGED;
    memcpy(packet.ID, m_userId, sizeof(packet.ID));
    packet_size =
        g_RagConnection->GetPacketSize(HEADER_CA_CONNECT_INFO_CHANGED);
    g_RagConnection->SendPacket(packet_size, (char *)&packet);
  }

  CheckExeHashFromAccServer();
  if (g_passwordEncrypt) {
    struct PACKET_CA_REQ_HASH packet;
    int packet_size;

    packet.header = HEADER_CA_REQ_HASH;
    packet_size = g_RagConnection->GetPacketSize(HEADER_CA_REQ_HASH);
    g_RagConnection->SendPacket(packet_size, (char *)&packet);
    // m_wndWait->SetMsg(g_MsgStrMgr->GetMsgStr(MSI_WAITING_RESPONSE_FROM_SERVER),
    // 16, 1);
    return;
  }

  if (g_serviceType != ServiceType::kKorea) {
    struct PACKET_CA_LOGIN packet;
    int packet_size;

    packet.header = HEADER_CA_LOGIN;
    packet.version = g_version;
    strncpy(packet.username, m_userId, sizeof(packet.username));
    strncpy(packet.password, m_userPassword, sizeof(packet.password));
    packet.client_type = g_clientType;  // GetAccountType();
    packet_size = g_RagConnection->GetPacketSize(HEADER_CA_LOGIN);
    g_RagConnection->SendPacket(packet_size, (char *)&packet);
  } else {
    struct PACKET_CA_LOGIN_CHANNEL packet;
    int packet_size;

    packet.header = HEADER_CA_LOGIN_CHANNEL;
    packet.version = g_version;
    strncpy(packet.username, m_userId, sizeof(packet.username));
    strncpy(packet.password, m_userPassword, sizeof(packet.password));
    strcpy(packet.ip_address, "111.111.111.111");
    memset(packet.mac_address, 0x11, sizeof(packet.mac_address));
    packet.clienttype = g_clientType;
    packet.channeling_corp = g_isGravityID;
    packet_size = g_RagConnection->GetPacketSize(HEADER_CA_LOGIN_CHANNEL);
    g_RagConnection->SendPacket(packet_size, (char *)&packet);
  }

  // CUIWaitWnd *waitwnd =
  //    (CUIWaitWnd *)g_WindowMgr->MakeWindow(WID_WAITWND);
  // waitwnd->SetMsg(g_MsgStrMgr->GetMsgStr(MSI_WAITING_RESPONSE_FROM_SERVER),
  // 16, 1);
}

void CLoginMode::ConnectToCharServer() {
  // Connection to char server
  struct PACKET_CH_ENTER packet;
  int packet_size;

  g_RagConnection->Disconnect();

  LOG(info, "Connecting to the char server ({}:{}) ...", g_charServerAddr.ip,
      g_charServerAddr.port);
  m_isConnected = g_RagConnection->Connect(&g_charServerAddr);
  // WinMainNpKeyStopEncryption();
  if (!m_isConnected) {
    LOG(error, "Failed to connect to the char server");
    g_RagConnection->Disconnect();
    /*str = MsgStr(MSI_SERVER_CONNECTION_FAILED);
    if (UIWindowMgr::ErrorMsg(&g_windowMgr, str, 1, 1, 1, 0) != 203)
    {
    g_mustPumpOutReceiveQueue = 0;
    }*/
    m_next_sub_mode = 3;
    return;
  }

  packet.header = HEADER_CH_ENTER;
  packet.client_type = g_clientType;
  packet.auth_code = m_authCode;
  packet.account_id = m_account_id;
  packet.user_level = m_userLevel;
  packet.Sex = g_Session->GetSex();
  g_mustPumpOutReceiveQueue = true;
  packet_size = g_RagConnection->GetPacketSize(HEADER_CH_ENTER);
  g_RagConnection->SendPacket(packet_size, (char *)&packet);
}

void CLoginMode::ConnectToZoneServer() {
  // Connection to zone server
  LOG(info, "Connecting to the zone server ({}:{}) ...", g_zoneServerAddr.ip,
      g_zoneServerAddr.port);
  m_isConnected = g_RagConnection->Connect(&g_zoneServerAddr);
  if (!m_isConnected) {
    LOG(error, "Failed to connect to the zone server");
    g_RagConnection->Disconnect();
    /*str = MsgStr(MSI_SERVER_CONNECTION_FAILED);
    if (UIWindowMgr::ErrorMsg(&g_windowMgr, str, 1, 1, 1, 0) != 203)
    {
    g_mustPumpOutReceiveQueue = 0;
    }*/
    m_next_sub_mode = 3;
    return;
  }

  struct PACKET_CZ_ENTER packet;

  packet.PacketType = HEADER_CZ_ENTER;
  // CLoginMode::SetPaddingValue(v2, &pad, 2);
  // CLoginMode::SetPaddingValue(v2, (char *)&packet.AID + 2, 1);
  // CLoginMode::SetPaddingValue(v2, (char *)&packet.AuthCode + 3, 4);
  packet.clientTime = GetTick();
  packet.AuthCode = m_authCode;
  packet.GID = m_char_id;
  packet.AID = m_account_id;
  packet.Sex = g_Session->GetSex();
  int packet_size = g_RagConnection->GetPacketSize(HEADER_CZ_ENTER);
  g_RagConnection->SendPacket(packet_size, (char *)&packet);
  g_RagConnection->SetBlock(true);
  // wnd = (UIWaitWnd *)UIWindowMgr::MakeWindow(&g_windowMgr,
  // WID_WAITWND);  str = MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER);
  // wnd->SetMsg(str, 16, 1);
}

void CLoginMode::PollNetworkStatus() {
  char buffer[2048];

  if (!g_RagConnection->Poll()) {
    g_ModeMgr->GetCurMode()->SendMsg(1, 0, 0, 0);
  }

  if (g_mustPumpOutReceiveQueue) {
    unsigned int aid;
    if (g_RagConnection->Recv((char *)&aid, 4, 1)) {
      g_mustPumpOutReceiveQueue = false;
    }
    return;
  }

  int size_of_buffer;
  while (g_RagConnection->RecvPacket(buffer, &size_of_buffer)) {
    const short packet_type = g_RagConnection->GetPacketType(buffer);
    switch (packet_type) {
      case HEADER_AC_ACCEPT_LOGIN:
        Ac_Accept_Login(buffer);
        break;
      case HEADER_AC_REFUSE_LOGIN:
        Ac_Refuse_Login(buffer);
        break;
      case HEADER_HC_ACCEPT_ENTER:
        Hc_Accept_Enter(buffer);
        break;
      case HEADER_HC_REFUSE_ENTER:
        Hc_Refuse_Enter(buffer);
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
        // Sc_Notify_Ban(buffer);
        return;
      case HEADER_AC_EVENT_RESULT:
        break;
      case HEADER_HC_BLOCK_CHARACTER:
        break;
      case HEADER_SC_BILLING_INFO:
        break;
      case HEADER_AC_ASK_PNGAMEROOM:
        break;
      case HEADER_SC_ACK_ENCRYPTION:
        break;
      case HEADER_AC_ACK_HASH:
        break;
      case HEADER_AC_NOTIFY_ERROR:
        break;
      case HEADER_PING:
        // Do nothing
        break;
      case HEADER_HC_CHARNOTBEENSELECTED:
        break;
      case HEADER_HC_ACK_IS_VALID_CHARNAME:
        break;
      case HEADER_HC_ACK_CHANGE_CHARNAME:
        break;
      case HEADER_HC_REFUSE_SELECTCHAR:
        break;
      case HEADER_ZC_AID:
        break;
      default:
        LOG(error, "Received unknown packet {}", packet_type);
        return;
    };
  }
  // ResetQueue
}

void CLoginMode::Ac_Accept_Login(const char *buffer) {
  struct PACKET_AC_ACCEPT_LOGIN *packet =
      (struct PACKET_AC_ACCEPT_LOGIN *)buffer;
  char sex;

  m_authCode = packet->auth_code;
  m_account_id = packet->account_id;
  m_userLevel = packet->user_level;

  if (packet->sex < 0xA) {
    sex = packet->sex;
  } else {
    sex = packet->sex - 10;
  }

  g_Session->SetSex(sex);
  // g_Session->SetTextType(false, false);
  m_numServer = (packet->packet_len - sizeof(PACKET_AC_ACCEPT_LOGIN)) /
                sizeof(CHAR_SERVER_INFO);
  memcpy(m_serverInfo, &(packet->server_info),
         m_numServer * sizeof(CHAR_SERVER_INFO));
  g_RagConnection->Disconnect();
  g_passwordWrong = false;
  m_next_sub_mode = 6;
}

void CLoginMode::Ac_Refuse_Login(const char *buffer) {
  struct PACKET_AC_REFUSE_LOGIN *packet =
      (struct PACKET_AC_REFUSE_LOGIN *)buffer;
  std::string msg;

  if (packet->error_code != 18) {
    g_RagConnection->Disconnect();
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
      SendMsg(MM_QUIT, 0, 0, 0);
      break;
    default:
      msg = g_MsgStrMgr->GetMsgStr(MSI_ACCESS_DENIED);
  };
  g_WindowMgr->ErrorMsg(msg, 0, 1, 0, 0);
}

void CLoginMode::CheckExeHashFromAccServer() {}

void CLoginMode::Hc_Accept_Enter(const char *buffer) {
  struct PACKET_HC_ACCEPT_ENTER *packet =
      (struct PACKET_HC_ACCEPT_ENTER *)buffer;

  /*memcpy(&m_billingInfo, 0, sizeof(m_billingInfo));
  m_billingInfo.code = ntohl(m_billingInfo.code);
  m_billingInfo.time1 = ntohl(m_billingInfo.time1);
  m_billingInfo.time2 = ntohl(m_billingInfo.time2);*/
  m_num_char = (packet->packet_len - sizeof(PACKET_HC_ACCEPT_ENTER)) /
               sizeof(CharacterInfo);
  memcpy(m_charInfo, packet->charinfo, m_num_char * sizeof(CharacterInfo));
  m_next_sub_mode = 7;
}

void CLoginMode::Hc_Refuse_Enter(const char *buffer) {
  struct PACKET_HC_REFUSE_ENTER *packet =
      (struct PACKET_HC_REFUSE_ENTER *)buffer;
  std::string msg;
  int change_msg;

  g_RagConnection->Disconnect();
  if (packet->error_code == 1) {
    change_msg = 1;
    msg = g_MsgStrMgr->GetMsgStr(MSI_ID_MISMATCH);
  } else {
    change_msg = 0;
    msg = g_MsgStrMgr->GetMsgStr(MSI_ACCESS_DENIED);
  }
  g_WindowMgr->ErrorMsg(msg, 0, 1, change_msg, 0);
}

void CLoginMode::Hc_Accept_Makechar(const char *buffer) {
  struct PACKET_HC_ACCEPT_MAKECHAR *packet =
      (struct PACKET_HC_ACCEPT_MAKECHAR *)buffer;

  memcpy(&m_charInfo[m_num_char], &packet->charinfo,
         sizeof(m_charInfo[m_num_char]));
  m_next_sub_mode = 7;
  m_num_char++;
}

void CLoginMode::Hc_Refuse_Makechar(const char *buffer) {
  struct PACKET_HC_REFUSE_MAKECHAR *packet =
      (struct PACKET_HC_REFUSE_MAKECHAR *)buffer;
  std::string msg;

  switch (packet->error_code) {
    case 0x0:
      msg = g_MsgStrMgr->GetMsgStr(MSI_CHARACTER_NAME_ALREADY_EXISTS);
      break;
    case 0x1:
      msg = g_MsgStrMgr->GetMsgStr(MSI_LIMIT_AGE);
      break;
    case 0x2:
      msg = g_MsgStrMgr->GetMsgStr(MSI_LIMIT_CHAR_DELETE);
      break;
    case 0x3:
      msg = g_MsgStrMgr->GetMsgStr(MSI_FR_ERR_MKCHAR_INVALID_SLOT);
      break;
    case 0xB:
      msg = g_MsgStrMgr->GetMsgStr(MSI_NEED_PREMIUM_SERVICE);
      break;
    default:
      msg = g_MsgStrMgr->GetMsgStr(MSI_CHARACTER_CREATION_DENIED);
  };
  g_WindowMgr->ErrorMsg(msg, 0, 1, 0, 0);
  m_next_sub_mode = 7;
}

void CLoginMode::Hc_Accept_Deletechar(const char *buffer) {
  CharacterInfo tmp_char_infos[0xC];
  unsigned int char_index = m_num_char;
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

  m_num_char--;
  memcpy(&m_charInfo, tmp_char_infos, m_num_char * sizeof(m_charInfo[0]));
  m_next_sub_mode = 7;
}

void CLoginMode::Hc_Refuse_Deletechar(const char *buffer) {
  struct PACKET_HC_REFUSE_DELETECHAR *packet =
      (struct PACKET_HC_REFUSE_DELETECHAR *)buffer;
  std::string msg;

  if (packet->error_code) {
    if (packet->error_code == 1) {
      msg = g_MsgStrMgr->GetMsgStr(MSI_FR_ERR_DELCHAR_INVALID_SLOT);
    } else {
      msg = g_MsgStrMgr->GetMsgStr(MSI_CANNOT_DELETE_CHARACTER);
    }
  } else if (g_serviceType != ServiceType::kKorea) {
    msg = g_MsgStrMgr->GetMsgStr(MSI_CANNOT_DELETE_CHARACTER_EMAIL);
  } else {
    msg = g_MsgStrMgr->GetMsgStr(MSI_CANNOT_DELETE_CHARACTER_PEOPLE_REG_NUMBER);
  }

  g_WindowMgr->ErrorMsg(msg, 0, 1, 0, 0);
  m_next_sub_mode = 7;
}

void CLoginMode::Zc_Accept_Enter(const char *buffer) {
  struct PACKET_ZC_ACCEPT_ENTER *packet =
      (struct PACKET_ZC_ACCEPT_ENTER *)buffer;
  g_Session->SetServerTime(packet->startTime);
  g_Session->SetPlayerPosDir(
      (packet->PosDir[1] >> 6) | 4 * packet->PosDir[0],
      (packet->PosDir[2] >> 4) | 16 * (packet->PosDir[1] & 0x3F),
      packet->PosDir[2] & 0xF);

  LOG(info, "Entering zone server. The current map is {}", m_current_map);
  g_ModeMgr->Switch(ModeType::kGame, m_current_map);
  g_RagConnection->SetBlock(false);
  // wnd = (UIWaitWnd *)g_WindowMgr->MakeWindow(WID_WAITWND);
  // str = MsgStr(MSI_PLEASE_BE_PATIENT);
  // wnd->SetMsg(str, 17, 1);
}

void CLoginMode::Zc_Accept_Enter2(const char *buffer) {
  struct PACKET_ZC_ACCEPT_ENTER2 *packet =
      (struct PACKET_ZC_ACCEPT_ENTER2 *)buffer;
  Zc_Accept_Enter(buffer);
}

void CLoginMode::Hc_Notify_Zonesvr(const char *buffer) {
  struct PACKET_HC_NOTIFY_ZONESVR *packet =
      (struct PACKET_HC_NOTIFY_ZONESVR *)buffer;
  struct in_addr ip;

  m_char_id = packet->char_id;
  m_current_map = reinterpret_cast<char *>(packet->map_name);
  ip.s_addr = packet->addr.ip;
  inet_ntop(AF_INET, &ip, g_zoneServerAddr.ip, sizeof(g_zoneServerAddr.ip));
  g_zoneServerAddr.port = packet->addr.port;
  g_RagConnection->Disconnect();
  m_next_sub_mode = 12;
}

void CLoginMode::Zc_Refuse_Enter(const char *buffer) {
  PACKET_ZC_REFUSE_ENTER *packet = (PACKET_ZC_REFUSE_ENTER *)buffer;
  std::string msg;

  switch (packet->error) {
    case 0:
      msg = g_MsgStrMgr->GetMsgStr(MSI_CLIENTTYPEMISMATCH);
      break;
    case 1:
      msg = g_MsgStrMgr->GetMsgStr(MSI_ID_MISMATCH);
      break;
    default:
      msg = g_MsgStrMgr->GetMsgStr(MSI_ACCESS_DENIED);
  };
  g_WindowMgr->ErrorMsg(msg, 0, 1, 0, 0);
  g_RagConnection->Disconnect();
  m_next_sub_mode = 3;
}
