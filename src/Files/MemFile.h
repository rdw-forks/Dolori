#ifndef DOLORI_FILES_MEMFILE_H_
#define DOLORI_FILES_MEMFILE_H_

#include <sys/types.h>

class CMemFile {
 public:
  virtual ~CMemFile() = default;

  virtual size_t GetSize() = 0;
  virtual const unsigned char* Read(off_t, size_t) = 0;
};

#endif  // DOLORI_FILES_MEMFILE_H_
