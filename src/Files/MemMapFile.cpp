#include "Files/MemMapFile.h"

CMemMapFile::CMemMapFile()
    : m_dwFileSize(),
      m_dwOpenOffset(),
      m_dwOpenSize(),
      m_dwFileMappingSize(),
      m_dwAllocationGranuarity(),
      m_pFile() {
#ifdef _WIN32
  m_hFile = nullptr;
  m_hFileMap = nullptr;
#else
  m_fd = 0;
#endif
}

CMemMapFile::~CMemMapFile() { Close(); }

bool CMemMapFile::Open(const char *name) {
#ifdef _WIN32
  m_hFile = CreateFileA(name, GENERIC_READ, FILE_SHARE_READ, nullptr,
                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
  if (m_hFile == INVALID_HANDLE_VALUE) {
    m_hFile = nullptr;
    return false;
  }
  m_dwFileSize = GetFileSize(m_hFile, 0);
  m_dwOpenOffset = 0;
  m_dwOpenSize = 0;
  m_hFileMap = CreateFileMappingA(m_hFile, nullptr, PAGE_READONLY, 0, 0, name);
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
  m_dwFileMappingSize = m_dwFileSize;

  return true;
}

void CMemMapFile::Close() {
#ifdef _WIN32
  if (m_dwFileMappingSize && m_pFile) {
    UnmapViewOfFile(m_pFile);
    m_pFile = nullptr;
  }
  if (m_hFileMap) {
    CloseHandle(m_hFileMap);
    m_hFileMap = nullptr;
  }
  if (m_hFile) {
    CloseHandle(m_hFile);
    m_hFile = nullptr;
  }
#else
  if (m_pFile) {
    munmap(m_pFile, m_dwFileMappingSize);
    m_pFile = nullptr;
  }

  if (m_fd != -1) {
    close(m_fd);
    m_fd = -1;
  }
#endif
}

size_t CMemMapFile::GetSize() { return m_dwFileSize; }

const unsigned char *CMemMapFile::Read(off_t offset, size_t size) {
  size_t bufferSize;

  if (m_dwFileMappingSize) {
    if (offset >= m_dwOpenOffset &&
        m_dwOpenOffset + m_dwOpenSize >= offset + size) {
      return m_pFile + offset - m_dwOpenOffset;
    }

    if (m_pFile) {
#ifdef _WIN32
      UnmapViewOfFile(m_pFile);
#else
      munmap(m_pFile, m_dwFileMappingSize);
#endif
      m_pFile = nullptr;
    }
    if (m_dwFileMappingSize) {
      do {
        if (m_dwFileMappingSize < size) {
          break;
        }

        m_dwOpenSize = m_dwFileMappingSize;
        m_dwOpenOffset = offset & m_dwAllocationGranuarity;
        if (m_dwOpenOffset + m_dwFileMappingSize <= m_dwFileSize) {
#ifdef _WIN32
          m_pFile = static_cast<unsigned char *>(
              MapViewOfFile(m_hFileMap, PAGE_READWRITE, 0, m_dwOpenOffset,
                            m_dwFileMappingSize));
#else
          m_pFile = static_cast<unsigned char *>(mmap(NULL, m_dwFileMappingSize,
                                                      PROT_READ, MAP_PRIVATE,
                                                      m_fd, m_dwOpenOffset));
#endif
        } else {
#ifdef _WIN32
          m_pFile = static_cast<unsigned char *>(
              MapViewOfFile(m_hFileMap, PAGE_READWRITE, 0, m_dwOpenOffset, 0));
#else
          m_pFile = static_cast<unsigned char *>(
              mmap(NULL, m_dwFileMappingSize - m_dwOpenOffset, PROT_READ,
                   MAP_PRIVATE, m_fd, m_dwOpenOffset));
#endif
          m_dwOpenSize = m_dwFileSize - m_dwOpenOffset;
        }

        if (m_pFile) {
          return m_pFile + offset - m_dwOpenOffset;
        }

        m_dwFileMappingSize = m_dwFileMappingSize >> 1;
      } while (m_dwFileMappingSize);
    }
#ifdef _WIN32
    CloseHandle(m_hFileMap);
    m_hFileMap = nullptr;
#endif
    m_pFile = nullptr;
    m_dwOpenSize = 0;
    m_dwFileMappingSize = 0;
  }

  if (m_dwOpenSize < size) {
    m_dwOpenSize = size;
    if (m_pFileBuf.data()) {
      bufferSize = m_pFileBuf.size();
    } else {
      bufferSize = 0;
    }

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

#ifdef _WIN32
  DWORD bytes_read;
  SetFilePointer(m_hFile, offset, 0, 0);
  ReadFile(m_hFile, m_pFileBuf.data(), static_cast<DWORD>(size), &bytes_read,
           nullptr);
#else
  ssize_t bytes_read;
  lseek(m_fd, offset, SEEK_SET);
  bytes_read = read(m_fd, m_pFileBuf.data(), size);
#endif

  return m_pFile;
}

void CMemMapFile::Init() {
#ifdef _WIN32
  SYSTEM_INFO systemInfo;
  GetSystemInfo(&systemInfo);
  m_dwAllocationGranuarity = 0 - systemInfo.dwAllocationGranularity;
  m_hFile = nullptr;
  m_hFileMap = nullptr;
#else
  m_dwAllocationGranuarity = 0;
  m_fd = -1;
#endif
  m_dwFileMappingSize = 0x20000000;
  m_pFile = nullptr;
  m_dwFileSize = 0;
  m_dwOpenOffset = 0;
  m_dwOpenSize = 0;
}
