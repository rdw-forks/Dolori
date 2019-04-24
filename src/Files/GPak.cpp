#include "Files/GPak.h"

#ifdef _WIN32
#define ZLIB_WINAPI
#endif

#include <string.h>
#include <iostream>

#include <grfcrypt.h>
#include <zlib.h>
#include "Common/debug.h"

#define GRF_RES_HEADER "Master of Magic"

#pragma pack(push, 1)

struct GrfHeader {
  char Magic[16];  // "Master of Magic" +\0
  char Key[14];    // 0x01 -&gt; 0x0E, or 0x00 -&gt; 0x00 (no encryption)
  uint32_t FileTableOffset;  // The location of the file table
  uint32_t Seed;             // What is the value of randomly
  uint32_t FilesCount;  // The actual number of files = FilesCount - Seed - 7
  uint32_t Version;     // GRF file version: 0x102, 0x103, 0x200
};

#pragma pack(pop)

CGPak::CGPak() : m_FileVer(), m_PakInfoOffset(), m_memFile() { Init(); }

bool CGPak::Open(std::shared_ptr<CMemFile> memFile) {
  bool result = false;

  if (!memFile) {
    return false;
  }

  m_memFile = memFile;
  auto header = reinterpret_cast<const GrfHeader *>(
      m_memFile->Read(0, sizeof(GrfHeader)));
  if (memcmp(header->Magic, GRF_RES_HEADER, sizeof(header->Magic)) != 0) {
    LOG(error, "Failed to parse in-memory file");
    return false;
  }

  m_FileVer = header->Version;
  m_FileCount = header->FilesCount - header->Seed - 7;
  m_PakInfoOffset = header->FileTableOffset + sizeof(GrfHeader);

  switch (m_FileVer & 0xFF00) {
    case 0x100:
      result = OpenPak01();
      break;
    case 0x200:
      result = OpenPak02();
      break;
  }

  return result;
}

void CGPak::Init() {
  m_FileVer = 0;
  m_FileCount = 0;
  m_PakInfoOffset = 0;
  m_PakInfoSize = 0;
  m_PakPack.clear();
  m_pDecBuf.clear();
  m_memFile = nullptr;
  // InitializeCriticalSection(&m_csPak);
}

bool CGPak::OpenPak01() { return false; }

bool CGPak::OpenPak02() {
  std::string filename;
  const uint8_t *z_buffer = nullptr;
  size_t z_table_size = 0;
  uLongf table_size = 0;
  uint32_t cursor = 0;

  z_table_size = *reinterpret_cast<const uint32_t *>(
      m_memFile->Read(m_PakInfoOffset, sizeof(uint32_t)));
  table_size = *reinterpret_cast<const uint32_t *>(
      m_memFile->Read(m_PakInfoOffset + 4, sizeof(uint32_t)));
  z_buffer = m_memFile->Read(m_PakInfoOffset + 8, z_table_size);

  std::vector<uint8_t> buffer(table_size);
  int z_result =
      ::uncompress(buffer.data(), &table_size, z_buffer, z_table_size);
  if (z_result != Z_OK) {
    LOG(error, "uncompress failed with code {}", z_result);
    return false;
  }

  const auto p_char_buffer = reinterpret_cast<char *>(buffer.data());
  for (uint32_t i = 0; i < m_FileCount; i++) {
    std::string tmp_filename;
    PAK_PACK pak;

    tmp_filename = p_char_buffer + cursor;
    NormalizeFileName(tmp_filename, filename);
    pak.hash.SetString(filename);
    cursor += tmp_filename.length() + 1;

    const PAK_PACK *pak_buffer =
        reinterpret_cast<const PAK_PACK *>(p_char_buffer + cursor);
    pak.m_compressSize = pak_buffer->m_compressSize;
    pak.m_dataSize = pak_buffer->m_dataSize;
    pak.m_size = pak_buffer->m_size;
    pak.m_type = pak_buffer->m_type;
    pak.m_Offset = pak_buffer->m_Offset;
    cursor += 4 * sizeof(uint32_t) + sizeof(uint8_t);

    m_PakPack.push_front(std::move(pak));
  }

  return true;
}

bool CGPak::GetInfo(const std::string &filename, PAK_PACK *pakPack) const {
  if (m_PakPack.empty()) {
    return false;
  }

  const CHash hash(filename);
  const auto elem = std::find_if(
      std::cbegin(m_PakPack), std::cend(m_PakPack),
      [&hash](const PAK_PACK &pak) {
        return pak.hash == hash && pak.hash.GetString() == hash.GetString();
      });
  if (elem == std::cend(m_PakPack)) {
    return false;
  }

  if (pakPack) {
    std::copy_n(elem, 1, pakPack);
  }

  return true;
}

bool CGPak::GetData(const PAK_PACK *pakPack, void *buffer) {
  char keyschedule[0x80];
  char key[8];

  if (pakPack == nullptr || buffer == nullptr) {
    return false;
  }

  if (pakPack->m_dataSize == 0) {
    return false;
  }

  auto data = reinterpret_cast<const char *>(m_memFile->Read(
      pakPack->m_Offset + sizeof(GrfHeader), pakPack->m_dataSize));

  /* Create a key and use it to generate the key schedule */
  DES_CreateKeySchedule(keyschedule, key);

  /* Decrypt the data (if its encrypted) */
  std::vector<char> z_buffer(pakPack->m_dataSize);
  GRF_Process(z_buffer.data(), data, pakPack->m_dataSize, pakPack->m_type,
              pakPack->m_compressSize, keyschedule, GRFCRYPT_DECRYPT);

  uLongf size = pakPack->m_size;
  int z_result = ::uncompress(reinterpret_cast<Bytef *>(buffer), &size,
                              reinterpret_cast<const Bytef *>(z_buffer.data()),
                              pakPack->m_dataSize);
  if (z_result != Z_OK) {
    LOG(error, "uncompress failed with code {}", z_result);
    return false;
  }

  return true;
}

void CGPak::NormalizeFileName(const std::string &input, std::string &output) {
  output = input;

  std::replace(output.begin(), output.end(), '\\', '/');
}
