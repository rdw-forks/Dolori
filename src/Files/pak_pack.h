#ifndef DOLORI_FILES_PAK_PACK_H_
#define DOLORI_FILES_PAK_PACK_H_

#include <stdint.h>
#include <stdlib.h>

#include "Files/Hash.h"

#pragma pack(push, 1)

typedef struct _PAK_PACK {
  uint32_t m_compressSize;
  uint32_t m_dataSize;
  uint32_t m_size;
  uint8_t m_type;
  uint32_t m_Offset;
  CHash hash;
} PAK_PACK;

#pragma pack(pop)

#endif  // DOLORI_FILES_PAK_PACK_H_
