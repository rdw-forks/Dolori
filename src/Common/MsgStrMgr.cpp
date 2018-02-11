#include "MsgStrMgr.h"
#include "Files/File.h"

CMsgStrMgr::CMsgStrMgr() {}

CMsgStrMgr::~CMsgStrMgr() {}

void CMsgStrMgr::InitMsgStrings(const char* imf_name) {
  size_t file_size;
  CFile file;
  char* buffer;

  if (!file.Open(imf_name, 0)) return;
  file_size = file.GetLength();
  buffer = (char*)malloc(file_size);
  if (buffer) {
    file.Read(buffer, file_size);
    char* start_ptr = buffer;
    for (int i = 0; i < file_size; i++) {
      switch (buffer[i]) {
        case '\r':
          buffer[i] = '\0';
        case '\n':
          start_ptr = &buffer[i + 1];
          break;
        case '#':
          buffer[i] = '\0';
          m_msgStrings.push_back(start_ptr);
      };
    }
    free(buffer);
  }
  file.Close();
}

const char* CMsgStrMgr::GetMsgStr(MSGSTRINGID id) {
  if (m_msgStrings.size() > id) return m_msgStrings[id].c_str();

  return NULL;
}
