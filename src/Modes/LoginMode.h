#ifndef DOLORI_MODES_LOGINMODE_H_
#define DOLORI_MODES_LOGINMODE_H_

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include "../Common/AccountInfo.h"
#include "../Common/billing_info.h"
#include "../Common/character_info.h"
#include "../Common/server_addr.h"
#include "Mode.h"

class CLoginMode : public CMode {
 public:
  CLoginMode();
  ~CLoginMode();

  void OnInit(const char *);
  int OnRun();
  void OnExit();
  void OnUpdate();
  void OnChangeState(int);
  void PollNetworkStatus();

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
  void Hc_Notify_Zonesvr(const char *);

 private:
  int m_authCode;
  unsigned int m_accountId;
  unsigned int m_userLevel;
  int m_charParam[0x8];
  char m_makingCharName[0x40];
  char m_emailAddress[0x80];
  char m_userPassword[0x40];
  char m_userId[0x40];
  int m_numServer;
  int m_serverSelected;
  int m_numChar;
  unsigned int m_subModeStartTime;
  struct SERVER_ADDR m_serverInfo[0x64];
  struct CHARACTER_INFO m_charInfo[0xc];
  std::string m_wallPaperBmpName;
  struct BILLING_INFO m_billingInfo;
  unsigned int m_syncRequestTime;
  // UIWaitWnd *m_wndWait;
  std::vector<CAccountInfo> m_accountInfo;
  std::vector<CAccountInfo> m_accountInfo2;
  unsigned char m_multiLang;
  int m_nSelectedAccountNo;
  int m_nSelectedAccountNo2;
  std::string m_strErrorInfo;
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