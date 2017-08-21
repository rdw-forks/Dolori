#include "MemMapFile.h"

CMemMapFile::CMemMapFile() {}

CMemMapFile::~CMemMapFile() { Close(); }

bool CMemMapFile::Open(const char *name) {
#ifdef WIN32
  m_hFile = CreateFileA(name, GENERIC_READ, FILE_SHARE_READ, NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (m_hFile == INVALID_HANDLE_VALUE) {
    m_hFile = NULL;
    return false;
  }
  m_dwFileSize = GetFileSize(m_hFile, 0);
  m_dwOpenOffset = 0;
  m_dwOpenSize = 0;
  m_hFileMap = CreateFileMappingA(m_hFile, NULL, PAGE_READONLY, 0, 0, name);
  if (!m_hFileMap) {
    m_dwFileMappingSize = 0;
    return false;
  }
#else
  m_fd = open(name, O_RDONLY);
  if (m_fd == -1) {
    return false;
  }

  struct stat sb;
  if (fstat(m_fd, &sb) == -1) {
    m_dwFileMappingSize = 0;
    return false;
  }
  m_dwFileSize = sb.st_size;
  m_dwOpenOffset = 0;
  m_dwOpenSize = 0;
#endif

  return true;
}

void CMemMapFile::Close() {
#ifdef WIN32
  if (m_dwFileMappingSize && m_pFile) {
    UnmapViewOfFile(m_pFile);
    m_pFile = NULL;
  }
  if (m_hFileMap) {
    CloseHandle(m_hFileMap);
    m_hFileMap = NULL;
  }
  if (m_hFile) {
    CloseHandle(m_hFile);
    m_hFile = NULL;
  }
#else
  if (m_pFile) {
    munmap(m_pFile, m_dwFileMappingSize);
    m_pFile = NULL;
  }

  if (m_fd != -1) {
    close(m_fd);
    m_fd = -1;
  }
#endif
}

unsigned long CMemMapFile::GetSize() { return m_dwFileSize; }

const unsigned char *CMemMapFile::Read(unsigned long offset,
                                       unsigned long size) {
  size_t bufferSize;
  unsigned long dwRead;

  if (m_dwFileMappingSize) {
    if (offset >= m_dwOpenOffset &&
        m_dwOpenOffset + m_dwOpenSize >= offset + size)
      return m_pFile + offset - m_dwOpenOffset;
    if (m_pFile) {
#ifdef WIN32
      UnmapViewOfFile(m_pFile);
#else
      munmap(m_pFile, m_dwFileMappingSize);
#endif
      m_pFile = NULL;
    }
    if (m_dwFileMappingSize) {
      do {
        if (m_dwFileMappingSize < size) break;

        m_dwOpenSize = m_dwFileMappingSize;
        m_dwOpenOffset = offset & m_dwAllocationGranuarity;
        if (m_dwOpenOffset + m_dwFileMappingSize <= m_dwFileSize) {
#ifdef WIN32
          m_pFile = (unsigned char *)MapViewOfFile(
              m_hFileMap, PAGE_READWRITE, 0, m_dwOpenOffset,
              m_dwFileMappingSize);
#else
          m_pFile =
              (unsigned char *)mmap(NULL, m_dwFileMappingSize, PROT_READ,
                                          MAP_PRIVATE, m_fd, m_dwOpenOffset);
#endif
        } else {
#ifdef WIN32
          m_pFile = (unsigned char *)MapViewOfFile(
              m_hFileMap, PAGE_READWRITE, 0, m_dwOpenOffset, 0);
#else
          m_pFile =
              (unsigned char *)mmap(NULL, m_dwFileMappingSize, PROT_READ,
                                          MAP_PRIVATE, m_fd, m_dwOpenOffset);
#endif
          m_dwOpenSize = m_dwFileSize - m_dwOpenOffset;
        }

        if (m_pFile) return m_pFile + offset - m_dwOpenOffset;

        m_dwFileMappingSize = m_dwFileMappingSize >> 1;
      } while (m_dwFileMappingSize);
    }
#ifdef WIN32
    CloseHandle(m_hFileMap);
    m_hFileMap = NULL;
#endif
    m_pFile = NULL;
    m_dwOpenSize = 0;
    m_dwFileMappingSize = 0;
  }

  if (m_dwOpenSize < size) {
    m_dwOpenSize = size;
    if (m_pFileBuf.data())
      bufferSize = m_pFileBuf.size();
    else
      bufferSize = 0;
    // if (bufferSize >= size)
    //{
    //	if (m_pFileBuf[0] != '\0' && size < m_pFileBuf.size())
    //	{
    //		v14 = m_pFileBuf._First;
    //		v17 = (unsigned int)&v14[size];
    //		v20 = (int)m_pFileBuf._Last;
    //		m_pFileBuf._Last = (char *)v17;
    //		v22 = v20;
    //	}
    //}
    // else
    if (bufferSize < size) {
      m_pFileBuf.insert(m_pFileBuf.end(), size - bufferSize, 0);
    }
    m_pFile = m_pFileBuf.data();
  }
#ifdef WIN32
  SetFilePointer(m_hFile, offset, 0, 0);
  ReadFile(m_hFile, m_pFileBuf.data(), size, &dwRead, NULL);
#else
  lseek(m_fd, offset, SEEK_SET);
  dwRead = read(m_fd, m_pFileBuf.data(), size);
#endif

  return m_pFile;
}

void CMemMapFile::Init() {
#ifdef WIN32
  _SYSTEM_INFO systemInfo;
  GetSystemInfo(&systemInfo);
  m_dwAllocationGranuarity = -systemInfo.dwAllocationGranularity;
  m_hFile = NULL;
  m_hFileMap = NULL;
#else
  m_dwAllocationGranuarity = 0;
  m_fd = -1;
#endif
  m_dwFileMappingSize = 0x20000000;
  m_pFile = NULL;
  m_dwFileSize = 0;
  m_dwOpenOffset = 0;
  m_dwOpenSize = 0;
}
