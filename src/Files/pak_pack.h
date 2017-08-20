#ifndef DOLORI_FILES_PAK_PACK_H_
#define DOLORI_FILES_PAK_PACK_H_

#include "Hash.h"

typedef struct PAK_PACK {
  uint32_t m_dataSize;
  uint32_t m_compressSize;
  uint32_t m_size;
  uint32_t m_Offset;
  uint8_t m_type;
  CHash m_fName;
} PAK_PACK;

#endif  // DOLORI_FILES_PAK_PACK_H_
