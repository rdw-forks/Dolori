#ifndef DOLORI_CORE_FILEMGR_H_
#define DOLORI_CORE_FILEMGR_H_

#include <stdio.h>
#include <list>
#include "Files/GPak.h"
#include "Files/MemFile.h"

class CFileMgr {
 public:
  CFileMgr();
  ~CFileMgr();

  bool AddPak(char const *);
  // void *GetData(const char *, unsigned long *, bool);
  void *GetPak(char const *, size_t *);
  bool IsDataExist(const char *);
  // void *GetFile(const char *name, unsigned long *lpSize);

 private:
  std::list<std::pair<CMemFile *, CGPak *>> m_pakList;
};

#endif  // DOLORI_CORE_FILEMGR_H_
