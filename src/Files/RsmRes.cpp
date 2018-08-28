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
  m_textures.resize(textures_count);
  for (int32_t i = 0; i < textures_count; i++) {
    fp.Read(&texture_name, sizeof(texture_name));
    m_textures[i] = texture_name;
  }

  // Nodes
  char main_node_name[0x28];
  int32_t nodes_count;

  fp.Read(&main_node_name, sizeof(main_node_name));
  fp.Read(&nodes_count, sizeof(nodes_count));
  for (int32_t i = 0; i < nodes_count; i++) {
    auto node = std::make_shared<C3dNodeRes>();
    node->Load(m_version, fp);
    m_nodes[node->name] = std::move(node);
  }

  if (m_nodes.find(main_node_name) != std::cend(m_nodes)) {
    m_root_node = m_nodes[main_node_name];
  } else {
    m_root_node = std::begin(m_nodes)->second;
  }

  m_root_node->parent = nullptr;
  m_root_node->FetchChildren(m_nodes);

  // PosKeyFrame
  if (m_version >= 0x105) {
  }

  // Volume box

  return true;
}

std::shared_ptr<C3dNodeRes> CRsmRes::GetRootNode() { return m_root_node; }

const std::vector<std::string>& CRsmRes::GetTextures() const {
  return m_textures;
}
