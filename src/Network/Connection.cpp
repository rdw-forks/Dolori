#include "Network/Connection.h"

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <arpa/inet.h>  // For inet_addr
#include <errno.h>
#include <netinet/tcp.h>  // For TCP_NODELAY
#include <string.h>       // For memset()
#include <sys/socket.h>   // For socket(), connect(), send(), and recv()
#include <unistd.h>       // For close()
#define closesocket close
#define SOCKET_ERROR (-1)
#define INVALID_SOCKET (-1)
#endif

#include "Common/ErrorMsg.h"
#include "Common/GetTick.h"
#include "Network/RagConnection.h"

CConnection::CConnection()
    : m_socket(SOCKET_ERROR), m_bBlock(false), m_dwTime() {
  m_recvQueue.Init(40960);
  m_sendQueue.Init(40960);
  m_blockQueue.Init(40960);
}

CConnection::~CConnection() {}

bool CConnection::Startup() {
  bool result;
#ifdef _WIN32
  WSADATA data;

  if (WSAStartup(0x101u, &data)) {
    ErrorMsg("Failed to initialize Winsock");
    WSACleanup();
    result = false;
  } else {
    result = true;
  }
#else
  result = true;
#endif
  return result;
}

void CConnection::Cleanup() {
#ifdef _WIN32
  WSACleanup();
#endif
}

bool CConnection::Poll() {
  bool result;

  if (m_socket == INVALID_SOCKET) {
    result = true;
  } else {
    result = OnRecv() && OnSend();
  }

  return result;
}

bool CConnection::Connect(const ServerAddress &sa) {
  bool result;

  m_recvQueue.Init(40960);
  m_sendQueue.Init(40960);
  m_blockQueue.Init(40960);

  m_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (m_socket == INVALID_SOCKET) {
    return false;
  }

  u_long argp = 1;
  if (setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY,
                 reinterpret_cast<char *>(&argp),
                 sizeof(argp)) == SOCKET_ERROR) {
    return false;
  }
#ifdef _WIN32
  argp = 1;
  if (ioctlsocket(m_socket, FIONBIO, &argp) == SOCKET_ERROR) {
    ErrorMsg("Failed to setup select mode");
    return false;
  }
#endif

  memset(&m_addr, 0, sizeof(m_addr));

  m_addr.sin_addr.s_addr = inet_addr(sa.ip);
  m_addr.sin_family = AF_INET;
  m_addr.sin_port = htons(sa.port);

  if (connect(m_socket, reinterpret_cast<sockaddr *>(&m_addr),
              sizeof(m_addr)) != SOCKET_ERROR ||
#ifdef _WIN32
      WSAGetLastError() == WSAEWOULDBLOCK) {
#else
      errno == EWOULDBLOCK) {
#endif
    m_dwTime = 0;
    result = true;
  } else {
    result = false;
  }

  return result;
}

void CConnection::Disconnect() {
  if (m_socket != INVALID_SOCKET) {
    closesocket(m_socket);
    m_socket = INVALID_SOCKET;
    m_sendQueue.Init(40960);
    m_blockQueue.Init(40960);
  }
}

bool CConnection::OnSend() {
  int nb_sockets;
  int sent_bytes;
  struct timeval timeout;
  fd_set writefds;

  if (m_dwTime >= GetTick()) {
    return true;
  }

  while (m_sendQueue.GetSize()) {
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
#ifdef _WIN32
    writefds.fd_array[0] = m_socket;
    writefds.fd_count = 1;
#else
    FD_ZERO(&writefds);
    FD_SET(m_socket, &writefds);
#endif
    nb_sockets = select(m_socket + 1, 0, &writefds, 0, &timeout);
    if (nb_sockets <= 0) {
      return true;
    }

    sent_bytes =
        send(m_socket, m_sendQueue.GetDataPtr(), m_sendQueue.GetSize(), 0);
    if (sent_bytes == -1) {
#ifdef _WIN32
      int err = WSAGetLastError();
      if (err != WSAEWOULDBLOCK && err != WSAENOTCONN) {
#else
      if (errno != EWOULDBLOCK && errno != ENOTCONN) {
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

    if (m_dwTime >= GetTick()) {
      return true;
    }
  }

  return true;
}

bool CConnection::OnRecv() {
  int nb_sockets;
  int received_bytes;
  struct timeval timeout;
  fd_set readfds;
  char buffer[2048];

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
#ifdef _WIN32
  readfds.fd_array[0] = m_socket;
  readfds.fd_count = 1;
#else
  FD_ZERO(&readfds);
  FD_SET(m_socket, &readfds);
#endif
  nb_sockets = select(m_socket + 1, &readfds, 0, 0, &timeout);
  if (nb_sockets <= 0) {
    return true;
  }

  received_bytes = recv(m_socket, buffer, sizeof(buffer), 0);
  if (received_bytes > 0) {
    m_recvQueue.InsertData(received_bytes, buffer);
    return true;
  }

  if (m_socket != INVALID_SOCKET) {
    closesocket(m_socket);
    m_socket = INVALID_SOCKET;
    m_sendQueue.Init(40960);
    m_blockQueue.Init(40960);
  }

#ifdef _WIN32
  int err = WSAGetLastError();
  if (err != WSAEWOULDBLOCK && err != WSAENOTCONN) {
    return true;
  }
#else
  if (errno != EWOULDBLOCK && errno != ENOTCONN) {
    return true;
  }
#endif

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
