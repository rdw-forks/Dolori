#ifndef DOLORI_CORE_FILEMGR_H_
#define DOLORI_CORE_FILEMGR_H_

#include <list>
#include "../Files/GPak.h"
#include "../Files/MemFile.h"

class CFileMgr {
 public:
  CFileMgr();
  ~CFileMgr();

  bool AddPak(char const *);
  bool AddCipheredPak(char const *name, uint8_t *);
  void *GetData(const char *, unsigned long *, bool);
  void *GetPak(char const *, unsigned long *);
  void *GetFile(const char *name, unsigned long *lpSize);

 private:
  std::list<std::pair<CMemFile *, CGPak *>> m_pakList;
};

#endif  // DOLORI_CORE_FILEMGR_H_
