#include "Common/MsgStrMgr.h"

#include "Files/File.h"

CMsgStrMgr::CMsgStrMgr() {}

CMsgStrMgr::~CMsgStrMgr() {}

bool CMsgStrMgr::InitMsgStrings(const std::string& imf_name) {
  size_t file_size;
  CFile file;

  if (!file.Open(imf_name, 0)) {
    return false;
  }

  file_size = file.GetLength();
  std::vector<char> buffer(file_size);

  file.Read(buffer.data(), file_size);
  char* start_ptr = buffer.data();
  for (int i = 0; i < file_size; i++) {
    switch (buffer[i]) {
      case '\r':
        buffer[i] = '\0';
      case '\n':
        start_ptr = buffer.data() + i + 1;
        break;
      case '#':
        buffer[i] = '\0';
        m_msgStrings.push_back(start_ptr);
        break;
    };
  }

  file.Close();

  return true;
}

std::string CMsgStrMgr::GetMsgStr(MSGSTRINGID id) {
  if (m_msgStrings.size() > id) {
    return m_msgStrings[id];
  }

  return {};
}
