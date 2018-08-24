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

GND_SURFACE_FMT CGndRes::s_empty_surface;
GND_CELL_FMT CGndRes::s_empty_cell;

CGndRes::CGndRes()
    : m_width(), m_height(), m_lminfo(), m_surfaces(), m_cells() {}

CGndRes::~CGndRes() { Reset(); }

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
  fp.Read(&m_num_textures, sizeof(m_num_textures));
  fp.Read(&name_length, sizeof(name_length));
  for (uint32_t i = 0; i < m_num_textures; i++) {
    buffer = new char[name_length];
    fp.Read(buffer, name_length);
    m_tex_name_table.push_back(buffer);
  }

  // Lightmaps
  int32_t cell_x, cell_y, cell_size;
  fp.Read(&m_num_lightmaps, sizeof(m_num_lightmaps));
  fp.Read(&cell_x, sizeof(cell_x));
  fp.Read(&cell_y, sizeof(cell_y));
  fp.Read(&cell_size, sizeof(cell_size));
  m_lminfo = new LM_INFO[m_num_lightmaps];
  fp.Read(m_lminfo, m_num_lightmaps * sizeof(LM_INFO));

  // Surfaces
  fp.Read(&m_num_surfaces, sizeof(m_num_surfaces));
  m_surfaces = new GND_SURFACE_FMT[m_num_surfaces];
  fp.Read(m_surfaces, m_num_surfaces * sizeof(GND_SURFACE_FMT));

  // Cells
  m_num_cells = m_width * m_height;
  m_cells = new GND_CELL_FMT[m_num_cells];
  fp.Read(m_cells, m_num_cells * sizeof(GND_CELL_FMT));

  fp.Close();

  return true;
}

void CGndRes::Reset() {
  for (auto buffer : m_tex_name_table) {
    delete[] buffer;
  }
  m_tex_name_table.clear();

  if (m_lminfo != nullptr) {
    delete[] m_lminfo;
    m_lminfo = nullptr;
  }

  if (m_surfaces != nullptr) {
    delete[] m_surfaces;
    m_surfaces = nullptr;
  }

  if (m_cells != nullptr) {
    delete[] m_cells;
    m_cells = nullptr;
  }
}

float CGndRes::GetZoom() const { return m_zoom; }

int32_t CGndRes::GetWidth() const { return m_width; }

int32_t CGndRes::GetHeight() const { return m_height; }

uint32_t CGndRes::GetSurfaceCount() const { return m_num_surfaces; }

const GND_SURFACE_FMT& CGndRes::GetSurface(unsigned int index) {
  if (index < m_num_surfaces) {
    return m_surfaces[index];
  }

  return s_empty_surface;
}

const GND_CELL_FMT& CGndRes::GetCell(unsigned int x, unsigned int y) {
  unsigned int index = x + y * m_width;

  if (index < m_num_cells) {
    return m_cells[index];
  }

  return s_empty_cell;
}

const char* CGndRes::GetTextureName(int texture_id) {
  if (texture_id < m_tex_name_table.size() && texture_id >= 0) {
    return m_tex_name_table[texture_id];
  }

  return nullptr;
}

const std::vector<char const*>& CGndRes::GetTextureNameTable() const {
  return m_tex_name_table;
}
