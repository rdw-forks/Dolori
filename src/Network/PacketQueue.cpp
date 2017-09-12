#include "PacketQueue.h"

#include <string.h>

CPacketQueue::CPacketQueue() {}

CPacketQueue::~CPacketQueue() {}

void CPacketQueue::Init(int size) {
  m_frontPos = 0;
  m_rearPos = 0;
  m_buffer.resize(size);

  if (m_buffer.empty())
    m_buf = NULL;
  else
    m_buf = m_buffer.data();
}

int CPacketQueue::GetSize() { return m_rearPos - m_frontPos; }

void CPacketQueue::InsertData(int size, const char *lpBuffer) {
  size_t delta_buffer;

  delta_buffer = m_buffer.size();
  if (m_rearPos + size > delta_buffer) {
    if (size + GetSize() > delta_buffer) {
      m_buffer.resize(delta_buffer * 2);

      if (m_buffer.empty())
        m_buf = NULL;
      else
        m_buf = m_buffer.data();
    }

    memmove(m_buf, &m_buf[m_frontPos], GetSize());
    m_rearPos -= m_frontPos;
    m_frontPos = 0;
  }
  memcpy(&m_buf[m_rearPos], lpBuffer, size);
  m_rearPos += size;
}

bool CPacketQueue::PeekData(int size, char *lpBuffer) {
  if (GetSize() >= size) {
    memcpy(lpBuffer, m_buf + m_frontPos, size);
    return true;
  }

  return false;
}

bool CPacketQueue::GetData(int size, char *lpBuffer) {
  bool result = false;

  if (GetSize() >= size) {
    memcpy(lpBuffer, m_buf + m_frontPos, size);
    m_frontPos += size;
    result = true;
  }

  return result;
}

bool CPacketQueue::RemoveData(int size) {
  if (GetSize() >= size) {
    m_frontPos = size + m_frontPos;
    return true;
  }

  return false;
}

char *CPacketQueue::GetDataPtr() { return m_buf + m_frontPos; }
