#include "Files/File.h"

#include <string.h>

#include "Common/Globals.h"
#include "Common/debug.h"

CFile::CFile() : m_fileStream(), m_buf(), m_size(), m_cursor(), m_fileName() {}

CFile::~CFile() { Close(); }

bool CFile::IsFileExist(const char* fName) {
  std::string full_name;

  MakeFileName(fName, full_name);
  return g_FileMgr->IsDataExist(full_name);
}

bool CFile::Open(const std::string& file_name, int nOpenFlags) {
  bool result;

  if (nOpenFlags != 0) {
    if ((nOpenFlags & 1) != 0) {
      m_fileName = file_name;
      m_fileStream.open(m_fileName, std::ios::binary);
      if (!m_fileStream.is_open()) {
        LOG(error, "Failed to open file: {}", m_fileName);
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
    MakeFileName(file_name, m_fileName);
    if (g_readFolderFirst) {
      if (OpenFromFolder(m_fileName)) {
        return true;
      }

      m_buf =
          static_cast<unsigned char*>(g_FileMgr->GetPak(m_fileName, &m_size));
    } else {
      m_buf =
          static_cast<unsigned char*>(g_FileMgr->GetPak(m_fileName, &m_size));
      if (m_buf == nullptr) {
        if (OpenFromFolder(m_fileName)) {
          return true;
        }
      }
    }

    result = (m_buf != nullptr);
  }

  return result;
}

bool CFile::OpenFromFolder(const std::string& filename) {
  m_fileStream.open(filename, std::ios::in | std::ios::binary);
  if (m_fileStream.is_open()) {
    std::streampos file_size = 0;

    file_size = m_fileStream.tellg();
    m_fileStream.seekg(0, std::ios::end);
    file_size = m_fileStream.tellg() - file_size;
    m_size = file_size;
    m_fileStream.seekg(0, std::ios::beg);

    if (m_size != 0) {
      m_buf = new uint8_t[m_size];
      if (m_buf != nullptr) {
        m_fileStream.read(reinterpret_cast<char*>(m_buf), m_size);
        m_fileStream.close();
        return true;
      }
    }

    m_fileStream.close();
  }

  return false;
}

bool CFile::Read(void* buffer, size_t nCount) {
  if (m_fileStream.is_open()) {
    m_fileStream.read(static_cast<char*>(buffer), nCount);
    return (m_fileStream.gcount() == nCount);
  }

  if (m_buf != nullptr && m_cursor + nCount <= m_size) {
    memcpy(buffer, &m_buf[m_cursor], nCount);
    m_cursor += nCount;
    return true;
  }

  return false;
}

bool CFile::Seek(intmax_t lOff, size_t nFrom) {
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

  if (m_buf != nullptr) {
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

    if (m_cursor <= m_size) {
      return true;
    }
    m_cursor = m_size;
  }

  return false;
}

bool CFile::Write(const void* buffer, size_t nCount) {
  bool result;

  if (m_fileStream.is_open()) {
    m_fileStream.write(static_cast<const char*>(buffer), nCount);
    result = true;
  } else {
    result = false;
  }

  return result;
}

void CFile::Close() {
  if (m_fileStream.is_open()) {
    m_fileStream.close();
    m_fileStream.clear();
  } else if (m_buf != nullptr) {
    delete[] m_buf;
    m_buf = nullptr;
  }
}

const std::string& CFile::GetFileName() const { return m_fileName; }

size_t CFile::GetLength() const { return m_size; }

const unsigned char* CFile::GetBuf() const { return m_buf; }

void CFile::MakeFileName(const std::string& input, std::string& output) {
  // TODO(LinkZ): Rewrite this method
  output = "data/" + input;
  NormalizeFileName(output, output);

  // char* delim_pos;
  // unsigned long sep_pos;
  // char temp[1024];

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

void CFile::NormalizeFileName(const std::string& input, std::string& output) {
  output = input;

  std::replace(output.begin(), output.end(), '\\', '/');
}
