#include "GPak.h"

#ifdef WIN32
#define ZLIB_WINAPI
#endif
#include <grfcrypt.h>
#include <string.h>
#include <zlib.h>
#include <iostream>

CGPak::CGPak() { Init(); }

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
  char filename[0x100];
  const uint8_t *z_buffer = NULL;
  size_t z_table_size = 0;
  size_t table_size = 0;
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
    NormalizeFileName(filename, (const char *)buffer + cursor);
    pak.m_fName.SetString(filename);
    cursor += filename_size + 1;
    pak.m_compressSize = *(uint32_t *)(buffer + cursor);
    pak.m_dataSize = *(uint32_t *)(buffer + cursor + 0x4);
    pak.m_size = *(uint32_t *)(buffer + cursor + 0x8);
    pak.m_type = *(uint8_t *)(buffer + cursor + 0xC);
    pak.m_Offset = *(uint32_t *)(buffer + cursor + 0xD);
    m_PakPack.push_back(pak);
    cursor += 0x11;
  }
  delete[] buffer;

  return true;
}

bool CGPak::GetInfo(CHash *fName, PAK_PACK *pakPack) {
  if (m_PakPack.empty()) return false;

  for (auto it = m_PakPack.begin(); it != m_PakPack.end(); ++it) {
    if (it->m_fName == *fName) {
      if (!strncmp(fName->GetString(), it->m_fName.GetString(), 0x100)) {
        if (pakPack) memcpy(pakPack, &(*it), sizeof(PAK_PACK));
        return true;
      }
    }
  }

  return false;
}

bool CGPak::GetData(PAK_PACK *pakPack, void *buffer) {
  char keyschedule[0x80], key[8];

  if (!pakPack || !buffer) return false;

  if (!pakPack->m_dataSize) return false;

  const char *data = (char *)m_memFile->Read(
      pakPack->m_Offset + sizeof(GRF_HEADER), pakPack->m_dataSize);

  char *z_data = (char *)malloc(pakPack->m_dataSize);
  if (!z_data) return false;

  /* Create a key and use it to generate the key schedule */
  DES_CreateKeySchedule(keyschedule, key);

  /* Decrypt the data (if its encrypted) */
  GRF_Process(z_data, data, pakPack->m_dataSize, pakPack->m_type,
              pakPack->m_compressSize, keyschedule, GRFCRYPT_DECRYPT);

  size_t size = pakPack->m_size;
  if (uncompress((Bytef *)buffer, (uLongf *)&size, (const Bytef *)z_data,
                 pakPack->m_dataSize) != Z_OK) {
    free(z_data);
    return false;
  }

  free(z_data);
  return true;
}

char *CGPak::NormalizeFileName(char *output, const char *input) {
  char *orig = output;

  for (; *input != '\0'; output++, input++)
    *output = (*input == '\\') ? '/' : *input;
  *output = '\0';

  return orig;
}
