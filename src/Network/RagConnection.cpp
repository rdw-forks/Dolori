#include "RagConnection.h"
//#include "PacketCipher.h"
#include "Packets.h"

#include <map>

std::map<int, int> g_packetLenMap;

CRagConnection::CRagConnection() {}

CRagConnection::~CRagConnection() {}

bool CRagConnection::SendPacket(int len, char *lpPacket) {
  if (!m_bDrop) {
    //*(unsigned short *)lpPacket ^= (unsigned short)PacketCipher->ChangeState(CPacketCipher::CLOCK);
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

  if (!m_recvQueue.PeekData(sizeof(header), (char *)&header))
    return false;

  if (g_packetLenMap[header] != -1) {
    nbOfReadBytes = LOWORD(CRagConnection::GetPacketSize(header));
  } else {
    if (!m_recvQueue.PeekData(sizeof(headerWithSize), (char *)&headerWithSize))
      return false;
    nbOfReadBytes = headerWithSize >> 16;
  }

  if (!m_recvQueue.GetData(nbOfReadBytes, lpBuffer))
    return false;

  if (len != NULL)
    *len = nbOfReadBytes;

  return true;
}

int CRagConnection::GetPacketSize(int packetType) {
  if (packetType == HEADER_ZC_SRPACKETR2_INIT)
    return 12;
  else if (packetType == HEADER_CZ_SRPACKETR2_START)
    return 4;
  else if (g_packetLenMap[packetType] <= 2)
    return 2;
  else
    return g_packetLenMap[packetType];
}

short CRagConnection::GetPacketType(const char *buffer) {
	return *((short*)buffer);
}