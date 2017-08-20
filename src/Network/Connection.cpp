#include "Connection.h"
#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>  // For socket(), connect(), send(), and recv()
#include <unistd.h>      // For close()
#endif
#include "../Common/GetTick.h"

CConnection::CConnection() {}

CConnection::~CConnection() {}

bool CConnection::Startup() {
#ifdef WIN32
  WSADATA data;
  bool result;

  if (WSAStartup(0x101u, &data)) {
    // ErrorMsg(aFailedToLoadWi);
    WSACleanup();
    result = false;
  } else
    result = true;
#else
  result = true;
#endif
  return result;
}

void CConnection::Cleanup() {
#ifdef WIN32
  WSACleanup();
#endif
}

bool CConnection::Poll() {
  bool result;

  if (m_socket == INVALID_SOCKET)
    result = true;
  else
    result = OnRecv() && OnSend();
  return result;
}

bool CConnection::Connect(const ServerAddress *sa) {
  bool result;

  m_recvQueue.Init(40960);
  m_sendQueue.Init(40960);
  m_blockQueue.Init(40960);

  m_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (m_socket == INVALID_SOCKET) return false;

  u_long argp = 1;
  if (setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, (char *)&argp,
                 sizeof(int)) == SOCKET_ERROR) {
    return false;
  }
  if (ioctlsocket(m_socket, FIONBIO, &argp) == SOCKET_ERROR) {
    return false;
  }

  memset(&m_addr, 0, sizeof(m_addr));

  m_addr.sin_addr.s_addr = inet_addr(sa->ip);
  m_addr.sin_family = AF_INET;
  m_addr.sin_port = htons(sa->port);

  if (connect(m_socket, (sockaddr *)&m_addr, 0x10) != SOCKET_ERROR ||
      WSAGetLastError() == WSAEWOULDBLOCK) {
    m_dwTime = 0;
    result = true;
  } else {
    WSAGetLastError();
    result = false;
  }

  return result;
}

void CConnection::Disconnect() {
  if (m_socket != -1) {
#ifdef WIN32
    closesocket(m_socket);
#else
    close(m_socket);
#endif
    m_socket = -1;
    m_sendQueue.Init(40960);
    m_blockQueue.Init(40960);
  }
}

bool CConnection::OnSend() {
  int nb_sockets;
  int sent_bytes;
  int err;
  struct timeval timeout;
  fd_set writefds;

  if (m_dwTime < GetTick()) {
    while (m_sendQueue.GetSize()) {
      timeout.tv_sec = 0;
      timeout.tv_usec = 0;
      writefds.fd_array[0] = m_socket;
      writefds.fd_count = 1;
      nb_sockets = select(0, 0, &writefds, 0, &timeout);
      if (nb_sockets != -1) {
        if (nb_sockets <= 0) return true;
        sent_bytes =
            send(m_socket, m_sendQueue.GetDataPtr(), m_sendQueue.GetSize(), 0);
        if (sent_bytes == -1) {
#ifdef WIN32
          err = WSAGetLastError();
          if (err != WSAEWOULDBLOCK && err != WSAENOTCONN) {
#else
#endif
            if (m_socket != INVALID_SOCKET) {
              closesocket(m_socket);
              m_socket = INVALID_SOCKET;
              m_sendQueue.Init(40960);
              m_blockQueue.Init(40960);
            }
            return false;
          }
        } else {
          m_sendQueue.RemoveData(sent_bytes);
        }
      }
      if (m_dwTime >= GetTick()) return true;
    }
  }
  return true;
}

bool CConnection::OnRecv() {
  int nb_sockets;
  int received_bytes;
  int err;
  struct timeval timeout;
  fd_set readfds;
  char lpBuffer[2048];

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  readfds.fd_array[0] = m_socket;
  readfds.fd_count = 1;
  nb_sockets = select(0, &readfds, 0, 0, &timeout);
  if (nb_sockets == -1 || nb_sockets <= 0) return true;
  received_bytes = recv(m_socket, lpBuffer, 2048, 0);
  if (received_bytes != -1) {
    if (received_bytes > 0) {
      m_recvQueue.InsertData(received_bytes, lpBuffer);
      return true;
    }
    goto LABEL_6;
  }
#ifdef WIN32
  err = WSAGetLastError();
  if (err != WSAEWOULDBLOCK && err != WSAENOTCONN) return true;
#else
#endif
LABEL_6:
  if (m_socket != INVALID_SOCKET) {
    closesocket(m_socket);
    m_socket = INVALID_SOCKET;
    m_sendQueue.Init(40960);
    m_blockQueue.Init(40960);
  }

  return false;
}

int CConnection::Recv(char *buf, int size, char mustRecv) {
  int result;

  if (mustRecv) {
    result = m_recvQueue.GetData(size, buf) != 0 ? size : 0;
  } else {
    if (size >= m_recvQueue.GetSize()) size = m_recvQueue.GetSize();
    m_recvQueue.GetData(size, buf);
    result = size;
  }
  return result;
}

void CConnection::SetBlock(bool bBlock) {
  m_bBlock = bBlock;
  if (!bBlock) {
    if (m_blockQueue.GetSize()) {
      int queue_size = m_blockQueue.GetSize();
      while (queue_size != 0) {
        m_sendQueue.InsertData(queue_size, m_blockQueue.GetDataPtr());
        m_blockQueue.RemoveData(queue_size);
        OnSend();
        queue_size = m_blockQueue.GetSize();
      }
    }
  }
}