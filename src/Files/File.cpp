#include "File.h"
#include <string.h>
#include "../Common/Globals.h"

CFile::CFile() {
  m_fileStream.clear();
  m_buf = NULL;
}

CFile::~CFile() { Close(); }

bool CFile::Open(const char* lpFileName, int nOpenFlags) {
  bool result;

  if (nOpenFlags) {
    if (nOpenFlags & 1) {
      strncpy(m_fileName, lpFileName, sizeof(m_fileName));
      m_fileStream.open(m_fileName, std::ios::binary);
      if (!m_fileStream.is_open()) {
        // ErrorMsg(m_fileName);
        result = false;
      } else {
        std::streampos file_size = 0;

        file_size = m_fileStream.tellg();
        m_fileStream.seekg(0, std::ios::end);
        file_size = m_fileStream.tellg() - file_size;
        m_size = file_size;
        m_fileStream.seekg(0, std::ios::beg);
        result = true;
      }
    } else {
      result = false;
    }
  } else {
    m_cursor = 0;
    MakeFileName(m_fileName, lpFileName, sizeof(m_fileName));
    if (g_readFolderFirst) {
      m_fileStream.open(m_fileName, std::ios::in | std::ios::binary);
      if (m_fileStream.is_open()) {
        std::streampos file_size = 0;

        file_size = m_fileStream.tellg();
        m_fileStream.seekg(0, std::ios::end);
        file_size = m_fileStream.tellg() - file_size;
        m_size = file_size;
        m_fileStream.seekg(0, std::ios::beg);

        if (m_size) {
          m_buf = (unsigned char*)malloc(m_size);
          if (m_buf) {
            m_fileStream.read((char*)m_buf, m_size);
            m_fileStream.close();
            return true;
          }
        }
        m_fileStream.close();
      }
      m_buf = (unsigned char*)g_FileMgr->GetPak(m_fileName, &m_size);
    } else {
      m_buf = (unsigned char*)g_FileMgr->GetPak(m_fileName, &m_size);
      if (!m_buf) {
        m_fileStream.open(m_fileName, std::ios::in | std::ios::binary);
        if (m_fileStream.is_open()) {
          std::streampos file_size = 0;

          file_size = m_fileStream.tellg();
          m_fileStream.seekg(0, std::ios::end);
          file_size = m_fileStream.tellg() - file_size;
          m_size = file_size;
          m_fileStream.seekg(0, std::ios::beg);

          if (m_size) {
            m_buf = (unsigned char*)malloc(m_size);
            if (m_buf) {
              m_fileStream.read((char*)m_buf, m_size);
              m_fileStream.close();
              return true;
            }
          }
          m_fileStream.close();
        }
      }
    }
    result = (m_buf != NULL);
  }

  return result;
}

bool CFile::Read(void* lpBuf, unsigned long nCount) {
  if (m_fileStream.is_open()) {
    m_fileStream.read((char*)lpBuf, nCount);
    return (m_fileStream.gcount() == nCount);
  }

  if (m_buf && m_cursor + nCount <= m_size) {
    memcpy(lpBuf, &m_buf[m_cursor], nCount);
    m_cursor += nCount;
    return true;
  }

  return false;
}

bool CFile::Seek(long lOff, unsigned long nFrom) {
  if (m_fileStream.is_open()) {
    switch (nFrom) {
      case SEEK_SET:
        m_fileStream.seekg(lOff, std::ios::beg);
        break;
      case SEEK_CUR:
        m_fileStream.seekg(lOff, std::ios::cur);
        break;
      case SEEK_END:
        m_fileStream.seekg(lOff, std::ios::end);
        break;
      default:
        return false;
    };
    return true;
  }
  if (m_buf) {
    switch (nFrom) {
      case SEEK_SET:
        m_cursor = lOff;
        break;
      case SEEK_CUR:
        m_cursor = lOff + m_cursor;
        break;
      case SEEK_END:
        m_cursor = lOff + m_size;
        break;
    }

    if (m_cursor <= m_size) return true;
    m_cursor = m_size;
  }
  return false;
}

bool CFile::Write(const void* lpBuf, unsigned long nCount) {
  bool result;

  if (m_fileStream.is_open())
    m_fileStream.write((const char*)lpBuf, nCount);
  else
    result = false;
  return result;
}

void CFile::Close() {
  if (m_fileStream.is_open()) {
    m_fileStream.close();
    m_fileStream.clear();
  } else if (m_buf) {
    free(m_buf);
    m_buf = NULL;
  }
}

char* CFile::GetFileName() { return m_fileName; }

size_t CFile::GetLength() { return m_size; }

const unsigned char* CFile::GetBuf() { return m_buf; }

void CFile::MakeFileName(char* output, const char* input,
                         unsigned long output_size) {
  char* delim_pos;
  unsigned long sep_pos;
  // char temp[1024];

  strncpy(output, "data/", output_size);
  strncat(output, input, output_size);
  NormalizeFileName(output, output);
  // TODO: Rewrite this method
  /*delim_pos = strstr(output, ":");
  if (delim_pos) {
    memcpy(temp, delim_pos - 1, output + strlen(output) + 2 - delim_pos);
    strncpy(output, temp, output_size);
  }
  while (strstr(output, "//")) {
    sep_pos = strstr(output, "//") - output;
    memcpy(temp, output, sep_pos);
    strncpy(&temp[sep_pos], &output[sep_pos + 1], sizeof(temp) - sep_pos);
    strncpy(output, temp, output_size);
  }*/
}

char* CFile::NormalizeFileName(char* output, const char* input) {
  char* orig = output;

  for (; *input != '\0'; output++, input++)
    *output = (*input == '\\') ? '/' : *input;

  return orig;
}
