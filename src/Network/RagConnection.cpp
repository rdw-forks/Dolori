#include "Network/RagConnection.h"

//#include "Network/PacketCipher.h"
#include "Common/debug.h"
#include "Network/Packets.h"

#ifndef _WIN32
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
  int32_t bytes_read;
  char header_with_size[4];
  uint16_t header;

  if (!m_recvQueue.PeekData(sizeof(header),
                            reinterpret_cast<char *>(&header))) {
    return false;
  }

  const auto packet_size = GetPacketSize(header);
  if (packet_size == -2) {
    return false;
  }

  if (packet_size != -1) {
    bytes_read = packet_size;
  } else {
    if (!m_recvQueue.PeekData(sizeof(header_with_size), header_with_size)) {
      return false;
    }

    bytes_read = *(reinterpret_cast<uint16_t *>(&header_with_size[2]));
  }

  if (!m_recvQueue.GetData(bytes_read, buffer)) {
    return false;
  }

  if (len != nullptr) {
    *len = bytes_read;
  }

  return true;
}

int32_t CRagConnection::GetPacketSize(uint16_t packet_type) const {
  const auto elem = m_packetLenMap.find(packet_type);
  if (elem != std::cend(m_packetLenMap)) {
    if (elem->second != -1 && elem->second <= 2) {
      return 2;
    }

    return elem->second;
  }

  LOG(error, "Unknown packet type: 0x{:x}", packet_type);
  return -2;
}

short CRagConnection::GetPacketType(const void *buffer) const {
  return *(static_cast<const short *>(buffer));
}

void CRagConnection::InitPacketMap() {
  m_packetLenMap[HEADER_ZC_SRPACKETR2_INIT] = 12;
  m_packetLenMap[HEADER_CZ_SRPACKETR2_START] = 4;
  m_packetLenMap[HEADER_CA_LOGIN] = sizeof(PACKET_CA_LOGIN);
  m_packetLenMap[HEADER_CA_LOGIN_CHANNEL] = sizeof(PACKET_CA_LOGIN_CHANNEL);
  m_packetLenMap[HEADER_AC_ACCEPT_LOGIN] = -1;
  m_packetLenMap[HEADER_AC_REFUSE_LOGIN] = sizeof(PACKET_AC_REFUSE_LOGIN);
  m_packetLenMap[HEADER_CH_ENTER] = sizeof(PACKET_CH_ENTER);
  m_packetLenMap[HEADER_HC_ACCEPT_ENTER] = -1;
  m_packetLenMap[HEADER_HC_ACCEPT_ENTER2] = -1;
  m_packetLenMap[HEADER_HC_CHARLIST_NOTIFY] = sizeof(PACKET_HC_CHARLIST_NOTIFY);
  m_packetLenMap[HEADER_HC_SECOND_PASSWD_LOGIN] =
      sizeof(PACKET_HC_SECOND_PASSWD_LOGIN);
  m_packetLenMap[HEADER_HC_REFUSE_ENTER] = sizeof(PACKET_HC_REFUSE_ENTER);
  m_packetLenMap[HEADER_AC_REFUSE_LOGIN_R2] = sizeof(PACKET_AC_REFUSE_LOGIN_R2);
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
  m_packetLenMap[HEADER_ZC_SAY_DIALOG] = sizeof(PACKET_ZC_SAY_DIALOG);
  m_packetLenMap[HEADER_ZC_WAIT_DIALOG] = sizeof(PACKET_ZC_WAIT_DIALOG);
  m_packetLenMap[HEADER_ZC_CLOSE_DIALOG] = sizeof(PACKET_ZC_CLOSE_DIALOG);
  m_packetLenMap[HEADER_ZC_SPRITE_CHANGE2] = sizeof(PACKET_ZC_SPRITE_CHANGE2);
  m_packetLenMap[HEADER_ZC_EQUIPMENT_ITEMLIST3] = -1;
  m_packetLenMap[HEADER_ZC_INVENTORY_ITEMLIST_EQUIP_V5] = -1;
  m_packetLenMap[HEADER_ZC_NOTIFY_MAPPROPERTY] =
      sizeof(PACKET_ZC_NOTIFY_MAPPROPERTY);
  m_packetLenMap[HEADER_ZC_MAPPROPERTY_R2] = sizeof(PACKET_ZC_MAPPROPERTY_R2);
  m_packetLenMap[HEADER_ZC_NOTIFY_STANDENTRY] =
      sizeof(PACKET_ZC_NOTIFY_STANDENTRY);
  m_packetLenMap[HEADER_ZC_NOTIFY_STANDENTRY8] = -1;
  m_packetLenMap[HEADER_ZC_SKILLINFO_LIST] = -1;
  m_packetLenMap[HEADER_ZC_SHORTCUT_KEY_LIST] =
      sizeof(PACKET_ZC_SHORTCUT_KEY_LIST);
  m_packetLenMap[HEADER_ZC_SHORTCUT_KEY_LIST_V2] =
      sizeof(PACKET_ZC_SHORTCUT_KEY_LIST_V2);
  m_packetLenMap[HEADER_ZC_LONGPAR_CHANGE] = sizeof(PACKET_ZC_LONGPAR_CHANGE);
  m_packetLenMap[HEADER_ZC_STATUS] = sizeof(PACKET_ZC_STATUS);
  m_packetLenMap[HEADER_ZC_PARTY_CONFIG] = sizeof(PACKET_ZC_PARTY_CONFIG);
  m_packetLenMap[HEADER_ZC_CONFIG_NOTIFY] = sizeof(PACKET_ZC_CONFIG_NOTIFY);
  m_packetLenMap[HEADER_ZC_BROADCAST2] = -1;
  m_packetLenMap[HEADER_ZC_EMOTION] = sizeof(PACKET_ZC_EMOTION);
  m_packetLenMap[HEADER_ZC_NAVIGATION_ACTIVE] =
      sizeof(PACKET_ZC_NAVIGATION_ACTIVE);
  m_packetLenMap[HEADER_ZC_QUEST_NOTIFY_EFFECT] =
      sizeof(PACKET_ZC_QUEST_NOTIFY_EFFECT);
  m_packetLenMap[HEADER_ZC_NOTIFY_TIME] = sizeof(PACKET_ZC_NOTIFY_TIME);
}
