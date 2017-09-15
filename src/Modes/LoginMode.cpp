#include "LoginMode.h"
#ifdef WIN32
#include <Ws2tcpip.h>
#define inet_ntop InetNtop
#else
#include <arpa/inet.h>
#endif
#include <string.h>
#include "../Common/GetTick.h"
#include "../Common/Globals.h"
#include "../Common/service_type.h"
#include "../Input/SDLEvents.h"
#include "../Network/Packets.h"
#include "../UI/UIBmp.h"
#include "../UI/UINoticeConfirmWnd.h"
#include "../UI/UISelectServerWnd.h"

CLoginMode::CLoginMode() {}

CLoginMode::~CLoginMode() {}

void CLoginMode::OnInit(const char *mode_name) {
  memset(m_charParam, 5, 6);
  m_charParam[6] = 0;
  m_charParam[7] = 1;
  m_makingCharName[0] = 0;
  m_emailAddress[0] = 0;
  m_wallPaperBmpName = TITLE_FILE;
  m_loopCond = true;
  m_nextSubMode = -1;
  // InitNPKCryptFuncTbl();
  m_subMode = g_loginStartMode;
  m_subModeCnt = 0;
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
  while (m_loopCond) {
    if (g_sysQuit) break;
    if (true /*!dword_7687C8*/) {
      if (m_nextSubMode != -1) {
        m_subMode = m_nextSubMode;
        m_subModeCnt = 0;
        m_nextSubMode = -1;
        OnChangeState(m_subMode);
      }
    }
    OnUpdate();
    ++m_subModeCnt;
  }
  // RunFadeOut(0);
  return 1;
}

void CLoginMode::OnExit() {}

int CLoginMode::SendMsg(size_t messageId, void *val1, void *val2, void *val3) {
  switch (messageId) {
    case MM_GOTOIDENTRY:
      g_mustPumpOutReceiveQueue = false;
      m_nextSubMode = 3;
      break;
    case LMM_CONNECT_TO_ACSVR:
      m_nextSubMode = 4;
      break;
    case LMM_PASSWORD:
      if (val1) strncpy(m_userPassword, (char *)val1, sizeof(m_userPassword));
      break;
    case LMM_ID:
      if (val1) strncpy(m_userId, (char *)val1, sizeof(m_userId));
      break;
    case LMM_GOTOSELECTACCOUNT: {
      size_t val = (size_t)val2;
      if (val == 135)
        g_ModeMgr->GetCurMode()->SendMsg(MM_QUIT, 0, 0, 0);
      else
        m_nextSubMode = 2;
    } break;
    case LMM_SELECTSVR: {
      m_serverSelected = (size_t)val1;
      if (m_serverSelected == -1) break;

      struct in_addr ip;
      ip.s_addr = m_serverInfo[m_serverSelected].ip;
      inet_ntop(AF_INET, &ip, g_charServerAddr.ip, sizeof(g_charServerAddr.ip));
      g_charServerAddr.port = m_serverInfo[m_serverSelected].port;
      m_nextSubMode = 5;
    } break;
    default:
      return CMode::SendMsg(messageId, val1, val2, val3);
  };

  return 0;
}

void CLoginMode::OnUpdate() {
  PollNetworkStatus();

  // Ping the server if necessary
  if ((m_subMode == 7 || m_subMode == 8 || m_subMode == 11 ||
       m_subMode == 19) &&
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
  if (g_Renderer->DrawScene()) g_Renderer->Flip();
}

void CLoginMode::OnChangeState(int state) {
  m_subModeStartTime = GetTick();
  m_isConnected = 1;

  switch (state) {
    case 0: {
      // Notice confirm window
      CBitmapRes *bitmap;
      CUINoticeConfirmWnd *wnd;

      m_wallPaperBmpName = UIBmp("유저인터페이스/login_interface/warning.bmp");
      bitmap = (CBitmapRes *)g_ResMgr->Get(m_wallPaperBmpName.c_str(), false);
      g_WindowMgr->SetWallpaper(bitmap);

      wnd =
          (CUINoticeConfirmWnd *)g_WindowMgr->MakeWindow(WID_NOTICECONFIRMWND);
      if (wnd) wnd->SendMsg(NULL, 80, (void *)LMM_GOTOSELECTACCOUNT, 0, 0, 0);
    } break;
    case 1:
      break;
    case 2:
      // Account server selection window
      // TODO
      // if (!InitAccountInfo())
      // SendMsg(30, 0, 0, 0);
      m_nextSubMode = 3;
      break;
    case 3: {
      // Login window
      // WinMainNpKeyStartEncryption();
      m_wallPaperBmpName = UIBmp("유저인터페이스/bgi_temp.bmp");
      CBitmapRes *res =
          (CBitmapRes *)g_ResMgr->Get(m_wallPaperBmpName.c_str(), false);
      g_WindowMgr->SetWallpaper(res);
      CUIFrameWnd *login_wnd = g_WindowMgr->MakeWindow(WID_LOGINWND);
      if (!g_hideAccountList && login_wnd)
        login_wnd->SendMsg(0, 88, 0, 0, 0, 0);
      return;
    }
    case 4: {
      // Connection to account server
      SERVER_ADDRESS server_addr;

      strncpy(server_addr.ip, g_accountAddr, sizeof(server_addr.ip));
      server_addr.port = atoi(g_accountPort);
      printf("Connecting to the account server ...\n");
      printf("IP: %s\nPort: %d\n", server_addr.ip, server_addr.port);
      m_isConnected = g_RagConnection->Connect(&server_addr);
      if (!m_isConnected) {
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

      if (g_serviceType != ServiceKorea) {
        struct PACKET_CA_LOGIN packet;
        int packet_size;

        packet.header = HEADER_CA_LOGIN;
        packet.version = g_version;
        strncpy(packet.username, m_userId, sizeof(packet.username));
        strncpy(packet.password, m_userPassword, sizeof(packet.password));
        packet.client_type = g_clientType;  // GetAccountType();
        packet_size = g_RagConnection->GetPacketSize(HEADER_CA_LOGIN);
        g_RagConnection->SendPacket(packet_size, (char *)&packet);
        // CUIWaitWnd *waitwnd =
        //    (CUIWaitWnd *)g_WindowMgr->MakeWindow(WID_WAITWND);
        // waitwnd->SetMsg(g_MsgStrMgr->GetMsgStr(MSI_WAITING_RESPONSE_FROM_SERVER),
        // 16, 1);
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
        // CUIWaitWnd *waitwnd =
        //    (CUIWaitWnd *)g_WindowMgr->MakeWindow(WID_WAITWND);
        // waitwnd->SetMsg(g_MsgStrMgr->GetMsgStr(MSI_WAITING_RESPONSE_FROM_SERVER),
        // 16, 1);
      }
    } break;
    case 5:
      // Connection to char server
      g_RagConnection->Disconnect();
      printf("Connecting to the char server ...\n");
      printf("IP: %s\nPort: %d\n", g_charServerAddr.ip, g_charServerAddr.port);
      m_isConnected = g_RagConnection->Connect(&g_charServerAddr);
      // WinMainNpKeyStopEncryption();
      if (!m_isConnected) {
        g_RagConnection->Disconnect();
        /*str = MsgStr(MSI_SERVER_CONNECTION_FAILED);
        if (UIWindowMgr::ErrorMsg(&g_windowMgr, str, 1, 1, 1, 0) != 203)
        {
                g_mustPumpOutReceiveQueue = 0;
                m_nextSubMode = 3;
        }*/
        return;
      }
      struct PACKET_CH_ENTER packet;
      int packet_size;

      packet.header = HEADER_CH_ENTER;
      packet.client_type = g_clientType;
      packet.auth_code = m_authCode;
      packet.account_id = m_accountId;
      packet.user_level = m_userLevel;
      packet.Sex = g_Session->GetSex();
      g_mustPumpOutReceiveQueue = 1;
      packet_size = g_RagConnection->GetPacketSize(HEADER_CH_ENTER);
      g_RagConnection->SendPacket(packet_size, (char *)&packet);
      return;
    case 6: {
      // Select char server
      CUISelectServerWnd *wnd =
          (CUISelectServerWnd *)g_WindowMgr->MakeWindow(WID_SELECTSERVERWND);

      if (wnd) wnd->SendMsg(0, 80, (void *)LMM_SELECTSVR, NULL, 0, 0);
      if (m_numServer < 0) {
        wnd->SendMsg(0, 40, 0, 0, 0, 0);
        return;
      }
      for (int i = 0; i < m_numServer; i++) {
        unsigned char *server_name = m_serverInfo[i].name;
        wnd->AddServer((char *)server_name);
      }
    } break;
    case 7:
      g_WindowMgr->MakeWindow(WID_SELECTCHARWND);
      break;
    case 12:
      // Connection to zone server
      m_isConnected = g_RagConnection->Connect(&g_zoneServerAddr);
      if (m_isConnected) {
        struct PACKET_CZ_ENTER packet;

        packet.PacketType = HEADER_CZ_ENTER;
        // CLoginMode::SetPaddingValue(v2, &pad, 2);
        // CLoginMode::SetPaddingValue(v2, (char *)&packet.AID + 2, 1);
        // CLoginMode::SetPaddingValue(v2, (char *)&packet.AuthCode + 3, 4);
        packet.clientTime = GetTick();
        packet.AuthCode = m_authCode;
        packet.GID = 0;
        packet.AID = 0;
        packet.Sex = g_Session->GetSex();
        packet_size = g_RagConnection->GetPacketSize(HEADER_CZ_ENTER);
        g_RagConnection->SendPacket(packet_size, (char *)&packet);
        g_RagConnection->SetBlock(true);
        // wnd = (UIWaitWnd *)UIWindowMgr::MakeWindow(&g_windowMgr,
        // WID_WAITWND);  str = MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER);
        // wnd->SetMsg(str, 16, 1);
      } else {
        g_RagConnection->Disconnect();
        /*str = MsgStr(MSI_SERVER_CONNECTION_FAILED);
        if (UIWindowMgr::ErrorMsg(&g_windowMgr, str, 1, 1, 1, 0) != 203)
        {
                g_mustPumpOutReceiveQueue = 0;
                m_nextSubMode = 3;
        }*/
      }
      return;
    case 13:
      // InitAccountInfo2()
      break;
  };
}

void CLoginMode::PollNetworkStatus() {
  char buffer[2048];

  if (!g_RagConnection->Poll()) g_ModeMgr->GetCurMode()->SendMsg(1, 0, 0, 0);

  if (g_mustPumpOutReceiveQueue) {
    unsigned int aid;
    if (g_RagConnection->Recv((char *)&aid, 4, 1))
      g_mustPumpOutReceiveQueue = false;
    return;
  }

  int size_of_buffer;
  if (!g_RagConnection->RecvPacket(buffer, &size_of_buffer)) return;

  short packet_type = g_RagConnection->GetPacketType(buffer);
  for (;;) {
    if (packet_type > HEADER_SC_NOTIFY_BAN) break;
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
      case HEADER_ZC_REFUSE_ENTER:
        g_WindowMgr->ErrorMsg(g_MsgStrMgr->GetMsgStr(MSI_ACCESS_DENIED), 0, 1,
                              0, 0);
        break;
      case HEADER_SC_NOTIFY_BAN:
        // Sc_Notify_Ban(buffer);
        return;
      default:
        return;
    };
    if (!g_RagConnection->RecvPacket(buffer, &size_of_buffer)) return;
  }
  switch (packet_type) {
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
    case HEADER_ZC_ACCEPT_ENTER2:
      break;
    default:
      break;
  };
  // ResetQueue
}

void CLoginMode::Ac_Accept_Login(const char *buffer) {
  struct PACKET_AC_ACCEPT_LOGIN *packet =
      (struct PACKET_AC_ACCEPT_LOGIN *)buffer;
  char sex;

  m_authCode = packet->auth_code;
  m_accountId = packet->account_id;
  m_userLevel = packet->user_level;

  if (packet->sex < 0xA)
    sex = packet->sex;
  else
    sex = packet->sex - 10;
  g_Session->SetSex(sex);
  // g_Session->SetTextType(false, false);
  m_numServer = (packet->packet_len - sizeof(PACKET_AC_ACCEPT_LOGIN)) /
                sizeof(CHAR_SERVER_INFO);
  memcpy(m_serverInfo, &(packet->server_info),
         m_numServer * sizeof(CHAR_SERVER_INFO));
  g_RagConnection->Disconnect();
  g_passwordWrong = false;
  m_nextSubMode = 6;
}

void CLoginMode::Ac_Refuse_Login(const char *buffer) {
  struct PACKET_AC_REFUSE_LOGIN *packet =
      (struct PACKET_AC_REFUSE_LOGIN *)buffer;

  if (packet->error_code != 18) g_RagConnection->Disconnect();
  switch (packet->error_code) {
    const char *msg;
    case 0:
      msg = g_MsgStrMgr->GetMsgStr(MSI_INCORRECT_USERID);
      g_WindowMgr->ErrorMsg(msg, 0, 1, 0, 0);
      break;
    case 1:
      msg = g_MsgStrMgr->GetMsgStr(MSI_INCORRECT_LOGIN_PASSWORD);
      g_WindowMgr->ErrorMsg(msg, 0, 1, 0, 0);
      break;
      // TODO ...
    case 3:
      msg = g_MsgStrMgr->GetMsgStr(MSI_BAN_PC_IP_LIMIT_ACCESS);
      g_WindowMgr->ErrorMsg(msg, 0, 1, 0, 0);
      break;
    case 5:
      msg = g_MsgStrMgr->GetMsgStr(MSI_INVALID_VERSION);
      g_WindowMgr->ErrorMsg(msg, 0, 1, 0, 0);
      // v2->vfptr->SendMsg((CMode *)v2, 2, 0, 0, 0);
      break;
    default:
      msg = g_MsgStrMgr->GetMsgStr(MSI_ACCESS_DENIED);
      g_WindowMgr->ErrorMsg(msg, 0, 1, 0, 0);
  };
}

void CLoginMode::CheckExeHashFromAccServer() {}

void CLoginMode::Hc_Accept_Enter(const char *buffer) {
  struct PACKET_HC_ACCEPT_ENTER *packet =
      (struct PACKET_HC_ACCEPT_ENTER *)buffer;

  memcpy(&m_billingInfo, &packet->packet_len, sizeof(this->m_billingInfo));
  m_billingInfo.code = ntohl(m_billingInfo.code);
  m_billingInfo.time1 = ntohl(m_billingInfo.time1);
  m_billingInfo.time2 = ntohl(m_billingInfo.time2);
  m_numChar = (packet->packet_len - sizeof(PACKET_HC_ACCEPT_ENTER)) /
              sizeof(CHARACTER_INFO);
  memcpy(m_charInfo, packet->charinfo, m_numChar * sizeof(CHARACTER_INFO));
  m_nextSubMode = 7;
}

void CLoginMode::Hc_Refuse_Enter(const char *buffer) {
  struct PACKET_HC_REFUSE_ENTER *packet =
      (struct PACKET_HC_REFUSE_ENTER *)buffer;
  const char *msg;
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

  memcpy(&g_charInfo, &packet->charinfo, sizeof(CHARACTER_INFO));
  memcpy(&m_charInfo[m_numChar], &packet->charinfo,
         sizeof(m_charInfo[m_numChar]));
  m_nextSubMode = 7;
  m_numChar++;
}

void CLoginMode::Hc_Refuse_Makechar(const char *buffer) {
  struct PACKET_HC_REFUSE_MAKECHAR *packet =
      (struct PACKET_HC_REFUSE_MAKECHAR *)buffer;

  switch (packet->error_code) {
    case 0x0:
      // v3 = MsgStr(MSI_CHARACTER_NAME_ALREADY_EXISTS);
      break;
    case 0x1:
      // v3 = MsgStr(MSI_LIMIT_AGE);
      break;
    case 0x2:
      // v3 = MsgStr(MSI_LIMIT_CHAR_DELETE);
      break;
    case 0x3:
      // v3 = MsgStr(MSI_FR_ERR_MKCHAR_INVALID_SLOT);
      break;
    case 0xB:
      // v3 = MsgStr(MSI_NEED_PREMIUM_SERVICE);
      break;
    default:
      // v3 = MsgStr(MSI_CHARACTER_CREATION_DENIED);
      break;
  }
  // g_windowMgr->ErrorMsg(v3, 0, 1, 0, 0);
  m_nextSubMode = 7;
}

void CLoginMode::Hc_Accept_Deletechar(const char *buffer) {
  struct CHARACTER_INFO tmp_char_infos[0xC];
  unsigned int char_index = m_numChar;
  unsigned int i = 0;
  unsigned int j = 0;

  // Remove deleted char's info from m_charInfo
  while (char_index) {
    if (m_charInfo->CharNum != g_selectedCharNum)
      memcpy(&tmp_char_infos[i++], &m_charInfo[j], sizeof(CHARACTER_INFO));

    j++;
    char_index--;
  }
  m_numChar--;
  memcpy(m_charInfo, tmp_char_infos, m_numChar * sizeof(CHARACTER_INFO));
  m_nextSubMode = 7;
}

void CLoginMode::Hc_Refuse_Deletechar(const char *buffer) {
  struct PACKET_HC_REFUSE_DELETECHAR *packet =
      (struct PACKET_HC_REFUSE_DELETECHAR *)buffer;

  if (packet->error_code) {
    // if (buf[2] == 1)
    //	v3 = MsgStr(MSI_FR_ERR_DELCHAR_INVALID_SLOT);
    // else
    //	v3 = MsgStr(MSI_CANNOT_DELETE_CHARACTER);
  } else if (g_serviceType != ServiceKorea) {
    // v3 = MsgStr(MSI_CANNOT_DELETE_CHARACTER_EMAIL);
  } else {
    // v3 = MsgStr(MSI_CANNOT_DELETE_CHARACTER_PEOPLE_REG_NUMBER);
  }
  // g_windowMgr->ErrorMsg(v3, 0, 1, 0, 0);
  m_nextSubMode = 7;
}

void CLoginMode::Zc_Accept_Enter(const char *buffer) {
  struct PACKET_ZC_ACCEPT_ENTER *packet =
      (struct PACKET_ZC_ACCEPT_ENTER *)buffer;
  char current_map[24];

  g_Session->SetServerTime(packet->startTime);
  g_Session->SetPlayerPosDir(
      (packet->PosDir[1] >> 6) | 4 * packet->PosDir[0],
      (packet->PosDir[2] >> 4) | 16 * (packet->PosDir[1] & 0x3F),
      packet->PosDir[2] & 0xF);
  snprintf(current_map, sizeof(current_map), "%s.rsw", g_currentMap);
  g_ModeMgr->Switch(1, current_map);
  // wnd = (UIWaitWnd *)g_WindowMgr->MakeWindow(WID_WAITWND);
  // str = MsgStr(MSI_PLEASE_BE_PATIENT);
  // wnd->SetMsg(str, 17, 1);
  g_RagConnection->SetBlock(false);
}

void CLoginMode::Hc_Notify_Zonesvr(const char *buffer) {
  struct PACKET_HC_NOTIFY_ZONESVR *packet =
      (struct PACKET_HC_NOTIFY_ZONESVR *)buffer;
  struct in_addr ip;

  strncpy(g_currentMap, (char *)packet->map_name, sizeof(g_currentMap));
  ip.s_addr = packet->addr.ip;
  inet_ntop(AF_INET, &ip, g_zoneServerAddr.ip, sizeof(g_zoneServerAddr.ip));
  g_zoneServerAddr.port = packet->addr.port;
}
