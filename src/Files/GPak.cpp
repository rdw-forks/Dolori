#include "GPak.h"

#ifdef WIN32
#define ZLIB_WINAPI
#endif
#include <string.h>
#include <zlib.h>

CGPak::CGPak() {
  Init();
}

CGPak::~CGPak() {}

bool CGPak::Open(CMemFile *memFile) {
  struct GRF_HEADER *header;

  if (!memFile) return false;

  m_memFile = memFile;
  header = (struct GRF_HEADER *)m_memFile->Read(0, sizeof(GRF_HEADER));
  if (memcmp(header->Magic, GRF_MAGIC_VALUE, sizeof(header->Magic)))
    return false;

  m_FileVer = header->Version;
  m_FileCount = header->FilesCount - header->Seed - 7;
  m_PakInfoOffset = header->FileTableOffset + sizeof(GRF_HEADER);
  switch (m_FileVer & 0xFF00) {
    case 0x100:
      if (OpenPak01()) return true;
    case 0x200:
      if (OpenPak02()) return true;
  }

  Init();
  return false;
}

void CGPak::Init() {
  m_FileVer = 0;
  m_FileCount = 0;
  m_PakInfoOffset = 0;
  m_PakInfoSize = 0;
  m_PakPack.clear();
  m_pDecBuf.clear();
  m_memFile = NULL;
  // InitializeCriticalSection(&m_csPak);
}

bool CGPak::OpenPak01() { return false; }

bool CGPak::OpenPak02() {
  const uint8_t *z_buffer = NULL;
  uint32_t z_table_size = 0;
  uint32_t table_size = 0;
  uint8_t *buffer = NULL;
  uint32_t cursor = 0;

  z_table_size = *(uint32_t *)m_memFile->Read(m_PakInfoOffset, 4);
  table_size = *(uint32_t *)m_memFile->Read(m_PakInfoOffset + 4, 4);
  z_buffer = m_memFile->Read(m_PakInfoOffset + 8, z_table_size);

  buffer = new uint8_t[table_size];
  if (uncompress(buffer, (uLongf *)&table_size, z_buffer, z_table_size) !=
      Z_OK) {
    delete[] buffer;
    return false;
  }

  for (uint32_t i = 0; i < m_FileCount; i++) {
    size_t filename_size;
    PAK_PACK pak;

    filename_size = strlen((char *)(buffer + cursor));
    if (filename_size >= 0x100) {
      delete[] buffer;
      return 0;
    }

    cursor += filename_size + 1;
    pak.m_compressSize = *(uint32_t *)(buffer + cursor);
    pak.m_dataSize = *(uint32_t *)(buffer + cursor + 0x4);
    pak.m_size = *(uint32_t *)(buffer + cursor + 0x8);
    pak.m_type = *(uint8_t *)(buffer + cursor + 0xC);
    pak.m_Offset = *(uint32_t *)(buffer + cursor + 0xD);
    pak.m_fName.SetString((const char *)buffer + cursor);
    m_PakPack.push_back(pak);
    cursor += 0x11;
  }
  delete[] buffer;

  return true;
}
