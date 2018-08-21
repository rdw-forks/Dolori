#include "Files/RsmRes.h"

#include "Common/debug.h"

#define RSM_RES_HEADER "GRSM"

#pragma pack(push)
#pragma pack(1)

typedef struct _RsmHeader {
  uint32_t magic;
  uint8_t version_major;
  uint8_t version_minor;
} RsmHeader;

#pragma pack(pop)

CRsmRes::CRsmRes() : m_version() { Reset(); }

CRes* CRsmRes::Clone() { return new CRsmRes(); }

void CRsmRes::Reset() { m_textures.clear(); }

bool CRsmRes::Load(const std::string& file_name) {
  uint32_t name_length;
  RsmHeader header;
  char* buffer;
  CFile fp;

  if (!fp.Open(file_name, false)) {
    LOG(error, "Failed to find file: {}", file_name);
    return false;
  }

  fp.Read(&header, sizeof(header));
  if (memcmp(&header.magic, RSM_RES_HEADER, sizeof(header.magic)) != 0) {
    LOG(error, "Failed to parse file: {}", file_name);
    return false;
  }

  m_version = (header.version_major << 8) | (header.version_minor);
  LOG(debug, "RSM file version: {:x}", m_version);

  // Info
  fp.Read(&m_anim_len, sizeof(m_anim_len));
  fp.Read(&m_shading_type, sizeof(m_shading_type));

  if (m_version >= 0x104) {
    fp.Read(&m_alpha, sizeof(m_alpha));
    m_alpha /= 255;
  } else {
    m_alpha = 1;
  }

  // Reserved
  fp.Seek(16, SEEK_CUR);

  // Textures
  char texture_name[0x28];
  int32_t textures_count;

  fp.Read(&textures_count, sizeof(textures_count));
  m_textures.reserve(textures_count);
  for (int32_t i = 0; i < textures_count; i++) {
    fp.Read(&texture_name, sizeof(texture_name));
    m_textures.push_back(texture_name);
  }

  // Nodes
  char node_name[0x28];
  int32_t nodes_count;

  fp.Read(&node_name, sizeof(node_name));
  fp.Read(&nodes_count, sizeof(nodes_count));
  for (int32_t i = 0; i < nodes_count; i++) {
    auto node = std::make_shared<C3dNodeRes>();
    node->Load(m_version, fp);
    m_object_list.push_back(std::move(node));
  }

  // PosKeyFrame
  if (m_version >= 0x105) {
  }

  // Volume box

  return true;
}
