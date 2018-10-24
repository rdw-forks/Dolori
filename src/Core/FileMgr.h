#ifndef DOLORI_CORE_FILEMGR_H_
#define DOLORI_CORE_FILEMGR_H_

#include <stdio.h>

#include <list>
#include <string>

#include "Files/GPak.h"
#include "Files/MemFile.h"

class CFileMgr {
 public:
  CFileMgr();

  bool AddPak(const std::string &pak_name);
  // void *GetData(const char *, unsigned long *, bool);
  void *GetPak(const std::string &file_name, size_t *file_size);
  bool IsDataExist(const std::string &file_name);
  // void *GetFile(const char *name, unsigned long *lpSize);

 private:
  std::list<std::pair<std::shared_ptr<CMemFile>, std::shared_ptr<CGPak>>>
      m_pakList;
};

#endif  // DOLORI_CORE_FILEMGR_H_
