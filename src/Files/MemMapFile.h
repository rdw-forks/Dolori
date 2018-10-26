#ifndef DOLORI_FILES_MEMMAPFILE_H_
#define DOLORI_FILES_MEMMAPFILE_H_

#ifdef WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdint>
#endif

#include <vector>

#include "Files/MemFile.h"

class CMemMapFile : public CMemFile {
 public:
  CMemMapFile();
  ~CMemMapFile();

  size_t GetSize() override;
  const unsigned char *Read(off_t offset, size_t size) override;

  bool Open(const char *);
  void Close();
  void Init();

 private:
#ifdef WIN32
  HANDLE m_hFile;
  HANDLE m_hFileMap;
#else
  int m_fd;
#endif
  size_t m_dwFileSize;
  uint32_t m_dwOpenOffset;
  size_t m_dwOpenSize;
  size_t m_dwFileMappingSize;
  uint32_t m_dwAllocationGranuarity;
  unsigned char *m_pFile;
  std::vector<unsigned char> m_pFileBuf;
};

#endif  // DOLORI_FILES_MEMMAPFILE_H_
