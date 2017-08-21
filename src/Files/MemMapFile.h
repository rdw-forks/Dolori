#ifndef DOLORI_FILES_MEMMAPFILE_H_
#define DOLORI_FILES_MEMMAPFILE_H_

#ifdef WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif
#include <vector>
#include "MemFile.h"

class CMemMapFile : public CMemFile {
 public:
  CMemMapFile();
  virtual ~CMemMapFile();

  bool open(const char *);
  void close();
  unsigned long size();
  const unsigned char *read(unsigned long, unsigned long);
  void init();

 private:
#ifdef WIN32
  HANDLE m_hFile;
  HANDLE m_hFileMap;
#else
  int m_fd;
#endif
  unsigned long m_dwFileSize;
  unsigned long m_dwOpenOffset;
  unsigned long m_dwOpenSize;
  unsigned long m_dwFileMappingSize;
  unsigned long m_dwAllocationGranuarity;
  unsigned char *m_pFile;
  std::vector<unsigned char> m_pFileBuf;
};

#endif  // DOLORI_FILES_MEMMAPFILE_H_
