#include "GndRes.h"
#include "Common/ErrorMsg.h"

GND_SURFACE_FMT CGndRes::s_empty_surface;
GND_CELL_FMT CGndRes::s_empty_cell;

CGndRes::CGndRes()
    : m_width(), m_height(), m_lminfo(), m_surfaces(), m_cells() {
  // m_new_ver = 0;
}

CGndRes::~CGndRes() { Reset(); }

CRes* CGndRes::Clone() { return new CGndRes(); }

bool CGndRes::Load(const char* filename) {
  uint32_t name_length;
  GND_HEADER header;
  char* buffer;
  CFile fp;

  if (!fp.Open(filename, false)) {
    std::string error = "Cannot find ";
    error += filename;
    ErrorMsg(error.c_str());
    return false;
  }

  fp.Read(&header, sizeof(header));
  if (header.magic != 'NGRG') {
    std::string error = "Illegal file format: ";
    error += filename;
    ErrorMsg(error.c_str());
    fp.Close();
    return false;
  }

  fp.Read(&m_width, sizeof(m_width));
  fp.Read(&m_height, sizeof(m_height));
  fp.Read(&m_zoom, sizeof(m_zoom));

  // Textures
  fp.Read(&m_num_textures, sizeof(m_num_textures));
  fp.Read(&name_length, sizeof(name_length));
  for (int i = 0; i < m_num_textures; i++) {
    buffer = new char[name_length];
    fp.Read(buffer, name_length);
    m_tex_name_table.push_back(buffer);
  }

  // Lightmaps
  int cell_x, cell_y, cell_size;
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
  m_tex_name_table.clear();

  if (m_lminfo) {
    delete m_lminfo;
    m_lminfo = nullptr;
  }

  if (m_surfaces) {
    delete m_surfaces;
    m_surfaces = nullptr;
  }

  if (m_cells) {
    delete m_cells;
    m_cells = nullptr;
  }
}

float CGndRes::GetZoom() { return m_zoom; }

int CGndRes::GetWidth() { return m_width; }

int CGndRes::GetHeight() { return m_height; }

uint32_t CGndRes::GetSurfaceCount() { return m_num_surfaces; }

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
