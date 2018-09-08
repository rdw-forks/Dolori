#include "Files/GndRes.h"

#include "Common/debug.h"
#include "Files/File.h"

#define GND_RES_HEADER "GRGN"

#pragma pack(push)
#pragma pack(1)

typedef struct _GndHeader {
  uint32_t magic;
  uint8_t version_major;
  uint8_t version_minor;
} GndHeader;

#pragma pack(pop)

CGndRes::CGndRes()
    : m_width(), m_height(), m_lightmaps(), m_surfaces(), m_cells() {}

CGndRes::~CGndRes() {}

CRes* CGndRes::Clone() { return new CGndRes(); }

bool CGndRes::Load(const std::string& filename) {
  uint32_t name_length;
  GndHeader header;
  char* buffer;
  CFile fp;

  if (!fp.Open(filename, false)) {
    LOG(error, "Failed to find file: {}", filename);
    return false;
  }

  fp.Read(&header, sizeof(header));
  if (memcmp(&header.magic, GND_RES_HEADER, sizeof(header.magic)) != 0) {
    LOG(error, "Failed to parse file: {}", filename);
    return false;
  }

  fp.Read(&m_width, sizeof(m_width));
  fp.Read(&m_height, sizeof(m_height));
  fp.Read(&m_zoom, sizeof(m_zoom));

  // Textures
  uint32_t num_textures;
  fp.Read(&num_textures, sizeof(num_textures));
  fp.Read(&name_length, sizeof(name_length));
  buffer = new char[name_length];
  for (uint32_t i = 0; i < num_textures; i++) {
    fp.Read(buffer, name_length);
    m_tex_name_table.push_back(buffer);
  }
  delete[] buffer;

  // Lightmaps
  int32_t cell_x, cell_y, cell_size;
  uint32_t num_lightmaps;
  fp.Read(&num_lightmaps, sizeof(num_lightmaps));
  fp.Read(&cell_x, sizeof(cell_x));
  fp.Read(&cell_y, sizeof(cell_y));
  fp.Read(&cell_size, sizeof(cell_size));

  m_lightmaps.resize(num_lightmaps);
  fp.Read(m_lightmaps.data(), num_lightmaps * sizeof(m_lightmaps[0]));

  // Surfaces;
  uint32_t num_surfaces;
  fp.Read(&num_surfaces, sizeof(num_surfaces));

  m_surfaces.resize(num_surfaces);
  fp.Read(m_surfaces.data(), num_surfaces * sizeof(m_surfaces[0]));

  // Cells
  const uint32_t num_cells = m_width * m_height;

  m_cells.resize(num_cells);
  fp.Read(m_cells.data(), num_cells * sizeof(m_cells[0]));

  fp.Close();

  return true;
}

void CGndRes::Reset() {
  m_tex_name_table.clear();
  m_lightmaps.clear();
  m_surfaces.clear();
  m_cells.clear();
}

float CGndRes::GetZoom() const { return m_zoom; }

int32_t CGndRes::GetWidth() const { return m_width; }

int32_t CGndRes::GetHeight() const { return m_height; }

uint32_t CGndRes::GetSurfaceCount() const { return m_surfaces.size(); }

const std::vector<LightmapInfo>& CGndRes::GetLightmaps() const {
  return m_lightmaps;
}

const GndSurfaceFmt& CGndRes::GetSurface(size_t index) {
  if (index < m_surfaces.size()) {
    return m_surfaces[index];
  }

  return {};
}

const GndCellFmt& CGndRes::GetCell(unsigned int x, unsigned int y) {
  const size_t index = x + y * m_width;
  if (index < m_cells.size()) {
    return m_cells[index];
  }

  return {};
}

const std::string& CGndRes::GetTextureName(size_t texture_id) {
  if (texture_id < m_tex_name_table.size()) {
    return m_tex_name_table[texture_id];
  }

  return {};
}

const std::vector<std::string>& CGndRes::GetTextureNameTable() const {
  return m_tex_name_table;
}
