#include "Network/RagConnection.h"

//#include "Network/PacketCipher.h"
#include "Common/debug.h"
#include "Network/Packets.h"

#ifndef WIN32
#define SOCKET_ERROR (-1)
#endif

CRagConnection::CRagConnection() : CConnection(), m_bDrop(false) {
  InitPacketMap();
}

CRagConnection::~CRagConnection() {}

bool CRagConnection::SendPacket(int len, char *packet) {
  if (!m_bDrop) {
    //*(unsigned short *)lpPacket ^= (unsigned
    // short)PacketCipher->ChangeState(CPacketCipher::CLOCK);
    if (m_socket != SOCKET_ERROR) {
      if (m_bBlock) {
        m_blockQueue.InsertData(len, packet);
      } else {
        m_sendQueue.InsertData(len, packet);
        OnSend();
      }
    }
  }

  return true;
}

bool CRagConnection::RecvPacket(char *buffer, int *len) {
  int nbOfReadBytes;
  unsigned int headerWithSize;
  unsigned short header;

  if (!m_recvQueue.PeekData(sizeof(header),
                            reinterpret_cast<char *>(&header))) {
    return false;
  }

  if (m_packetLenMap[header] != -1) {
    nbOfReadBytes = GetPacketSize(header);
  } else {
    if (!m_recvQueue.PeekData(sizeof(headerWithSize),
                              reinterpret_cast<char *>(&headerWithSize))) {
      return false;
    }

    nbOfReadBytes = headerWithSize >> 16;
  }

  if (!m_recvQueue.GetData(nbOfReadBytes, buffer)) {
    return false;
  }

  if (len != nullptr) {
    *len = nbOfReadBytes;
  }

  return true;
}

int CRagConnection::GetPacketSize(int packetType) {
  if (packetType == HEADER_ZC_SRPACKETR2_INIT) {
    return 12;
  }

  if (packetType == HEADER_CZ_SRPACKETR2_START) {
    return 4;
  }

  if (m_packetLenMap[packetType] <= 2) {
    return 2;
  }

  const auto elem = m_packetLenMap.find(packetType);
  if (elem != std::cend(m_packetLenMap)) {
    return elem->second;
  }

  LOG(error, "Unknown packet type: {}", packetType);
  return -2;
}

short CRagConnection::GetPacketType(const char *buffer) {
  return *(reinterpret_cast<const short *>(buffer));
}

void CRagConnection::InitPacketMap() {
  m_packetLenMap[HEADER_CA_LOGIN] = sizeof(PACKET_CA_LOGIN);
  m_packetLenMap[HEADER_CA_LOGIN_CHANNEL] = sizeof(PACKET_CA_LOGIN_CHANNEL);
  m_packetLenMap[HEADER_AC_ACCEPT_LOGIN] = -1;
  m_packetLenMap[HEADER_AC_REFUSE_LOGIN] = sizeof(PACKET_AC_REFUSE_LOGIN);
  m_packetLenMap[HEADER_CH_ENTER] = sizeof(PACKET_CH_ENTER);
  m_packetLenMap[HEADER_HC_ACCEPT_ENTER] = -1;
  m_packetLenMap[HEADER_HC_REFUSE_ENTER] = sizeof(PACKET_HC_REFUSE_ENTER);
  m_packetLenMap[HEADER_HC_BLOCK_CHARACTER] = -1;
  m_packetLenMap[HEADER_CH_SELECT_CHAR] = sizeof(PACKET_CH_SELECT_CHAR);
  m_packetLenMap[HEADER_CH_MAKE_CHAR] = sizeof(PACKET_CH_MAKE_CHAR);
  m_packetLenMap[HEADER_HC_ACCEPT_MAKECHAR] = sizeof(PACKET_HC_ACCEPT_MAKECHAR);
  m_packetLenMap[HEADER_HC_REFUSE_MAKECHAR] = sizeof(PACKET_HC_REFUSE_MAKECHAR);
  m_packetLenMap[HEADER_HC_NOTIFY_ZONESVR] = sizeof(PACKET_HC_NOTIFY_ZONESVR);
  m_packetLenMap[HEADER_ZC_AID] = sizeof(PACKET_ZC_AID);
  m_packetLenMap[HEADER_CZ_ENTER] = sizeof(PACKET_CZ_ENTER);
  m_packetLenMap[HEADER_CZ_ENTER2] = sizeof(PACKET_CZ_ENTER2);
  m_packetLenMap[HEADER_ZC_ACCEPT_ENTER] = sizeof(PACKET_ZC_ACCEPT_ENTER);
  m_packetLenMap[HEADER_ZC_ACCEPT_ENTER2] = sizeof(PACKET_ZC_ACCEPT_ENTER2);
  m_packetLenMap[HEADER_ZC_REFUSE_ENTER] = sizeof(PACKET_ZC_REFUSE_ENTER);
  m_packetLenMap[HEADER_ZC_NOTIFY_PLAYERCHAT] = -1;
  m_packetLenMap[HEADER_ZC_NPCACK_MAPMOVE] = sizeof(PACKET_ZC_NPCACK_MAPMOVE);
  m_packetLenMap[HEADER_ZC_COUPLESTATUS] = sizeof(PACKET_ZC_COUPLESTATUS);
  m_packetLenMap[HEADER_ZC_PAR_CHANGE] = sizeof(PACKET_ZC_PAR_CHANGE);
  m_packetLenMap[HEADER_ZC_ATTACK_RANGE] = sizeof(PACKET_ZC_ATTACK_RANGE);
}
