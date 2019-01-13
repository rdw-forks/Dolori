#ifndef DOLORI_NETWORK_CONNECTION_H_
#define DOLORI_NETWORK_CONNECTION_H_

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
#endif

#include "Network/PacketQueue.h"

struct ServerAddress {
  char ip[0x10];
  int port;
};

class CConnection {
 public:
  CConnection();
  virtual ~CConnection();

  bool Poll();
  bool Connect(const ServerAddress &sa);
  void Disconnect();
  int Recv(char *, int, char);
  void SetBlock(bool bBlock);
  static bool Startup();
  static void Cleanup();

 protected:
  bool OnSend();
  bool OnRecv();

 protected:
#ifdef _WIN32
  SOCKET m_socket;
#else
  int m_socket;
#endif
  struct sockaddr_in m_addr;
  bool m_bBlock;
  unsigned long m_dwTime;
  CPacketQueue m_sendQueue;
  CPacketQueue m_recvQueue;
  CPacketQueue m_blockQueue;
};

// class CConnection {
//	*
//		public void CConnection(const class CConnection &)
//		public void CConnection::CConnection()
//		public void CConnection::~CConnection()
//		public unsigned char CConnection::Connect(const struct
// ServerAddress *) 		public unsigned char IsConnect()
//		public unsigned char CConnection::Poll()
//		public void CConnection::Disconnect()
//		public void CConnection::Send(int, const char *)
//		public int CConnection::Recv(char *, int, unsigned char)
//		public void CConnection::ResetQueue()
//		public void CConnection::SetBlock(unsigned char)
//		public void SetDelay(unsigned long)
//		protected unsigned char CConnection::OnSend()
//		protected unsigned char CConnection::OnRecv()
//		protected void CConnection::OnConnect()
//		protected void CConnection::OnClose()
//		public static unsigned char CConnection::Startup()
//		public static void CConnection::Cleanup()
//		public unsigned char CConnection::CheckModulePt()
//		/* this+0x4 */ unsigned int m_socket
//	/* this+0x8 */ struct sockaddr_in m_addr
//
//		/* this+0x18 */ unsigned char m_bBlock
//		/* this+0x1c */ unsigned long m_dwTime
//	/* this+0x20 */ class CPacketQueue m_sendQueue
//
//	/* this+0x3c */ class CPacketQueue m_recvQueue
//
//	/* this+0x58 */ class CPacketQueue m_blockQueue
//
//		/* [0x0003:0x0003dd30] */ static  struct WSAData s_wsaData
//
//		/* [0x0003:0x0003dec0] */ static  struct HINSTANCE__ *
// s_wsmodule
//		/* [0x0003:0x0003df44] */ static  function  * s_wsSend
//		/* [0x0003:0x0003dec4] */ static  function  * s_wsRecv
//		public class CConnection & operator=(const class CConnection &)
//		public void __local_vftable_ctor_closure()
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_NETWORK_CONNECTION_H_
