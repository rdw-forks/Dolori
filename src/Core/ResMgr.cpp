#include "ResMgr.h"

#include "../Files/File.h"

CResMgr::CResMgr() {}

CResMgr::~CResMgr() {}

void CResMgr::ReadResNameTable(const char *resNameTable) {
  CFile* fp = new CFile();

  if (fp->Open(resNameTable, 0)) {
    size_t file_size = fp->GetLength();
    char* buffer;

    buffer = new char[file_size + 1];
    if (!buffer) return;

    if (!fp->Read(buffer, file_size)) {
      delete[] buffer;
      return;
    }

    buffer[file_size] = '\0';
    fp->Close();

    // Parse the content of the name table
    std::string a("");
    std::string b("");
    char* beg_of_line = buffer;
    for (size_t i = 0; i < file_size; i++) {
      char cur_char = buffer[i];

      if (cur_char == '\r' || cur_char == '\n') {
        buffer[i] = '\0';
        beg_of_line = &buffer[i + 1];
        continue;
      }

      if (cur_char == '#') {
        buffer[i] = '\0';
        // If we have a left element,
        // fetch the right one and fill the map
        if (a.length() > 0) {  
          b = beg_of_line;
          m_realResName[a] = b;
          a.clear();
          b.clear();
          beg_of_line = &buffer[i + 1];
          continue;
        }
        // Else we fetch what could be
        // a left element
        a = beg_of_line;
        beg_of_line = &buffer[i + 1];
      }
    }
    delete[] buffer;
  }
}

CRes* Get(const char* fNameInput, bool bRefresh) {
  if (!fNameInput) return NULL;
  return NULL;
}
