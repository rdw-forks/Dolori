#ifndef DOLORI_MODES_LOGINMODE_H_
#define DOLORI_MODES_LOGINMODE_H_

#include <string>
#include <vector>

#include "Common/AccountInfo.h"
#include "Common/character_info.h"
#include "Modes/Mode.h"
#include "Network/RagConnection.h"

typedef struct _ServerAddr {
  unsigned int ip;
  unsigned short port;
  unsigned char name[0x14];
  unsigned short usercount;
  unsigned short state;
  unsigned short property;
} ServerAddr;

typedef struct _BillingInfo {
  char dummy1;
  unsigned long code;
  unsigned long time1;
  unsigned long time2;
  char dummy2[0x7];
} BillingInfo;

typedef enum _LOGINMODE_MSG {
  LMM_CONNECT_TO_ACSVR = 0x2710,
  LMM_MAKECHARACTER = 0x2711,
  LMM_TRANSFERCHARACTER = 0x2712,
  LMM_SELECTSVR = 0x2713,
  LMM_SELECTCHARACTER = 0x2714,
  LMM_SENDCHARINFO = 0x2715,
  LMM_CANCEL = 0x2716,
  LMM_PASSWORD = 0x2717,
  LMM_ID = 0x2718,
  LMM_SELECT_CHARACTER = 0x2719,
  LMM_DELETE_CHARACTER = 0x271a,
  LMM_GOTO_LOGIN = 0x271b,
  LMM_SET_EMAIL_ADDRESS = 0x271c,
  LMM_GET_EMAIL_ADDRESS = 0x271d,
  LMM_GET_MAKING_CHAR_NAME = 0x271e,
  LMM_SET_MAKING_CHAR_NAME = 0x271f,
  LMM_GET_CHAR_PARAM = 0x2720,
  LMM_SET_CHAR_PARAM = 0x2721,
  LMM_GOTOSELECTACCOUNT = 0x2722,
  LMM_SELECTACCOUNT = 0x2723,
  LMM_GET_BILLING_INFO = 0x2724,
  LMM_DISCONNECT_ACSVR = 0x2725,
  LMM_SELECTACCOUNT2 = 0x2726,
  LMM_GOTOLICENCE = 0x2727,
} LOGINMODE_MSG;

class CLoginMode : public CMode {
 public:
  CLoginMode(CRagConnection *rag_connection, CUIWindowMgr *p_window_mgr);

  void OnInit(const std::string &) override;
  int OnRun() override;
  void OnExit() override;
  void *SendMsg(size_t, const void *val1 = nullptr, const void *val2 = nullptr,
                const void *val3 = nullptr) override;

  void OnUpdate();

 private:
  void OnChangeState(int);
  void PollNetworkStatus();

  void MakeLoginWindow();
  void ConnectToAccountServer();
  void ConnectToCharServer();
  void ConnectToZoneServer();

  void Ac_Accept_Login(const char *);
  void Ac_Refuse_Login(const char *);
  void CheckExeHashFromAccServer();
  void Hc_Accept_Enter(const char *);
  void Hc_Refuse_Enter(const char *);
  void Hc_Accept_Makechar(const char *);
  void Hc_Refuse_Makechar(const char *);
  void Hc_Accept_Deletechar(const char *);
  void Hc_Refuse_Deletechar(const char *);
  void Zc_Accept_Enter(const char *);
  void Zc_Accept_Enter2(const char *buffer);
  void Hc_Notify_Zonesvr(const char *);
  void Zc_Refuse_Enter(const char *buffer);

 private:
  int m_authCode;
  uint32_t m_account_id;
  uint32_t m_userLevel;
  int m_charParam[0x8];
  char m_makingCharName[0x40];
  char m_emailAddress[0x80];
  char m_userPassword[0x40];
  char m_userId[0x40];
  int m_numServer;
  size_t m_serverSelected;
  size_t m_selected_char;
  size_t m_num_char;
  uint32_t m_char_id;
  unsigned int m_subModeStartTime;
  ServerAddr m_serverInfo[0x64];
  CharacterInfo m_charInfo[0xc];
  std::string m_wallPaperBmpName;
  BillingInfo m_billingInfo;
  unsigned int m_syncRequestTime;
  CharacterInfo m_new_char_info;
  // UIWaitWnd *m_wndWait;
  std::vector<CAccountInfo> m_accountInfo;
  std::vector<CAccountInfo> m_accountInfo2;
  unsigned char m_multiLang;
  int m_nSelectedAccountNo;
  int m_nSelectedAccountNo2;
  std::string m_strErrorInfo;
  std::string m_current_map;
};

// class CLoginMode {
//	CMode, offset = 0x0
//
//		public void CLoginMode(const class CLoginMode &)
//		public void CLoginMode::CLoginMode()
//		public void CLoginMode::~CLoginMode()
//		public void CLoginMode::OnInit(const char *)
//		public int CLoginMode::OnRun()
//		public void CLoginMode::OnExit()
//		public void CLoginMode::OnUpdate()
//		public int CLoginMode::SendMsg(int, int, int, int)
//		public void CLoginMode::PreLoadAlwaysNeededRes()
//		public void CLoginMode::SetKeycryptErrorInfo(const char *)
//		private void CLoginMode::OnChangeState(int)
//		private void CLoginMode::PollNetworkStatus()
//		private void CLoginMode::OnProcessState(int)
//		private void CLoginMode::OnRenderState(int)
//		private void CLoginMode::OpenSettlePage()
//		private void CLoginMode::CheckPingTime()
//		private void CLoginMode::CheckExeHashFromAccServer()
//		private void CheckHashFromCharServer()
//		private int CLoginMode::GenerateExeHash(unsigned char *)
//		private char * CLoginMode::SetPaddingValue(char *, int)
//		/* this+0x40 */ int[0x8] m_charParam
//		/* this+0x60 */ char[0x40] m_makingCharName
//		/* this+0xa0 */ char[0x80] m_emaiAddress
//		/* this+0x120 */ char[0x40] m_userPassword
//		/* this+0x160 */ char[0x40] m_userId
//		/* this+0x1a0 */ int m_numServer
//		/* this+0x1a4 */ int m_serverSelected
//		/* this+0x1a8 */ int m_numChar
//		/* this+0x1ac */ unsigned long m_subModeStartTime
//		/* this+0x1b0 */ struct SERVER_ADDR[0x64] m_serverInfo
//		/* this+0xe30 */ struct CHARACTER_INFO[0xc] m_charInfo
//		/* this+0x1340 */ class std::string m_wallPaperBmpName
//
//		/* this+0x1350 */ struct BILLING_INFO m_billingInfo
//
//		/* this+0x1364 */ unsigned long m_syncRequestTime
//		/* this+0x1368 */ class UIWaitWnd * m_wndWait
//		private void CLoginMode::Ac_Accept_Login(const char *)
//		private void CLoginMode::Ac_Refuse_Login(const char *)
//		private void CLoginMode::Ac_Event_Result(const char *)
//		private void CLoginMode::Hc_Accept_Enter(const char *)
//		private void CLoginMode::Hc_Block_Character(const char *)
//		private void CLoginMode::Hc_Refuse_Enter(const char *)
//		private void CLoginMode::Hc_Accept_Makechar(const char *)
//		private void CLoginMode::Hc_Refuse_Makechar(const char *)
//		private void CLoginMode::Hc_Accept_Deletechar(const char *)
//		private void CLoginMode::Hc_Refuse_Deletechar(const char *)
//		private void CLoginMode::Hc_Notify_Zonesvr(const char *)
//		private void CLoginMode::Zc_Accept_Enter(const char *)
//		private void CLoginMode::Zc_Accept_Enter2(const char *)
//		private void CLoginMode::Zc_Refuse_Enter(const char *)
//		private void CLoginMode::Sc_Notify_Ban(const char *)
//		private void CLoginMode::Sc_Billing_Info(const char *)
//		private void CLoginMode::Ac_Ask_Pngameroom(const char *)
//		private void CLoginMode::Sc_Ack_Encryption(const char *)
//		private void CLoginMode::Ac_Ack_Hash(const char *)
//		private void CLoginMode::Ac_Notify_Error(const char *)
//		private void CLoginMode::Hc_Refuse_SelectChar(const char *)
//		private void CLoginMode::Zc_Aid(const char *)
//		private void CLoginMode::Hc_CharNotBeenSelected(const char *)
//		private void CLoginMode::Hc_Ack_Is_Valid_CharName(const char *)
//		private void CLoginMode::Hc_Ack_Change_CharName(const char *)
//		private void CLoginMode::SendCaIpSecurity()
//		private unsigned char CLoginMode::InitAccountInfo()
//		private unsigned char CLoginMode::InitAccountInfo2(int)
//		private int CLoginMode::SendKeycryptErrorInfo()
//		/* this+0x136c */ class std::vector<accountInfo,
// std::allocator<accountInfo> > m_accountInfo
//
//		/* this+0x137c */ class std::vector<accountInfo,
// std::allocator<accountInfo> > m_accountInfo2
//
//		/* this+0x138c */ unsigned char m_multiLang
//		/* this+0x1390 */ int m_nSelectedAccountNo
//		/* this+0x1394 */ int m_nSelectedAccountNo2
//		/* this+0x1398 */ class std::string m_strErrorInfo
//
//		public class CLoginMode & operator=(const class CLoginMode &)
//		public void __local_vftable_ctor_closure()
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_MODES_LOGINMODE_H_
