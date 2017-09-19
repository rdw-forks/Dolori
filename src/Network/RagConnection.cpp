#include "RagConnection.h"
//#include "PacketCipher.h"
#include "Packets.h"

#ifndef WIN32
#define SOCKET_ERROR (-1)
#endif

CRagConnection::CRagConnection() {
  m_socket = SOCKET_ERROR;
  m_bBlock = false;
  m_bDrop = false;
  m_dwTime = 0;
  m_recvQueue.Init(40960);
  m_sendQueue.Init(40960);
  m_blockQueue.Init(40960);
  InitPacketMap();
}

CRagConnection::~CRagConnection() {}

bool CRagConnection::SendPacket(int len, char *lpPacket) {
  if (!m_bDrop) {
    //*(unsigned short *)lpPacket ^= (unsigned
    // short)PacketCipher->ChangeState(CPacketCipher::CLOCK);
    if (m_socket != SOCKET_ERROR) {
      if (m_bBlock) {
        m_blockQueue.InsertData(len, lpPacket);
      } else {
        m_sendQueue.InsertData(len, lpPacket);
        OnSend();
      }
    }
  }

  return true;
}

bool CRagConnection::RecvPacket(char *lpBuffer, int *len) {
  int nbOfReadBytes;
  unsigned int headerWithSize;
  unsigned short header;

  if (!m_recvQueue.PeekData(sizeof(header), (char *)&header)) return false;

  if (m_packetLenMap[header] != -1) {
    nbOfReadBytes = GetPacketSize(header);
  } else {
    if (!m_recvQueue.PeekData(sizeof(headerWithSize), (char *)&headerWithSize))
      return false;
    nbOfReadBytes = headerWithSize >> 16;
  }

  if (!m_recvQueue.GetData(nbOfReadBytes, lpBuffer)) return false;

  if (len != NULL) *len = nbOfReadBytes;

  return true;
}

int CRagConnection::GetPacketSize(int packetType) {
  if (packetType == HEADER_ZC_SRPACKETR2_INIT) return 12;
  if (packetType == HEADER_CZ_SRPACKETR2_START) return 4;
  if (m_packetLenMap[packetType] <= 2) return 2;
  return m_packetLenMap[packetType];
}

short CRagConnection::GetPacketType(const char *buffer) {
  return *((short *)buffer);
}

void CRagConnection::InitPacketMap() {
  m_packetLenMap[HEADER_CA_LOGIN] = sizeof(PACKET_CA_LOGIN);
  m_packetLenMap[HEADER_AC_ACCEPT_LOGIN] = -1;
  m_packetLenMap[HEADER_AC_REFUSE_LOGIN] = sizeof(PACKET_AC_REFUSE_LOGIN);
  m_packetLenMap[HEADER_CH_ENTER] = sizeof(PACKET_CH_ENTER);
  m_packetLenMap[HEADER_HC_ACCEPT_ENTER] = -1;
  m_packetLenMap[HEADER_HC_REFUSE_ENTER] = sizeof(PACKET_HC_REFUSE_ENTER);
}
