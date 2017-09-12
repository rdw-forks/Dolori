#ifndef DOLORI_NETWORK_RAGCONNECTION_H_
#define DOLORI_NETWORK_RAGCONNECTION_H_

#include <map>
#include "Connection.h"

class CRagConnection : public CConnection {
 public:
  CRagConnection();
  ~CRagConnection();

  bool SendPacket(int, char *);
  bool RecvPacket(char *, int *);
  int GetPacketSize(int);
  short GetPacketType(const char *);

 protected:
  void InitPacketMap();

 private:
  bool m_bDrop;
  std::map<int, int> m_packetLenMap;
};

// class CRagConnection {
//	CConnection, offset = 0x0
//
//		public void CRagConnection(const class CRagConnection &)
//		public void CRagConnection::CRagConnection()
//		public unsigned char CRagConnection::SendPacket(int, const char
//*) 		public unsigned char CRagConnection::RecvPacket(char *)
//		public int CRagConnection::GetPacketSize(int)
//		public short CRagConnection::GetPacketType(const char *)
//		public static class CRagConnection & CRagConnection::instanceR()
//		protected unsigned char CRagConnection::IsFixedPacket(int)
//		protected void CRagConnection::InitPacketMap()
//		public class CRagConnection & operator=(const class
// CRagConnection
//&) 		public void CRagConnection::~CRagConnection()
//		public void __local_vftable_ctor_closure()
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_NETWORK_RAGCONNECTION_H_