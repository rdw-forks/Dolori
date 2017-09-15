#ifndef DOLORI_FILES_PAK_PACK_H_
#define DOLORI_FILES_PAK_PACK_H_

#include <stdlib.h>
#include "Hash.h"

typedef struct PAK_PACK {
  size_t m_dataSize;
  size_t m_compressSize;
  size_t m_size;
  uint32_t m_Offset;
  uint8_t m_type;
  CHash m_fName;
} PAK_PACK;

#endif  // DOLORI_FILES_PAK_PACK_H_
