#include "Render/RPFace.h"

CRPFace::CRPFace()
    : m_primType(GL_POLYGON),
      m_vertices(),
      m_texture_coords(),
      m_indices(),
      m_texture(),
      m_oows() {}

CRPFace::CRPFace(int num_vertices) : CRPFace() {
  m_vertices.resize(num_vertices);
  m_texture_coords.resize(num_vertices);
  m_oows.resize(num_vertices);
}

CRPFace::~CRPFace() {}

void CRPFace::set_texture(CTexture* texture) { m_texture = texture; }

void CRPFace::SetGeomInfo(int index, const TlVertex3d& vert) {
  if (index >= m_vertices.size() || index < 0) {
    return;
  }

  m_vertices[index] = vert.vertex;
  m_texture_coords[index] = vert.texture_coords;
  m_oows[index] = vert.oow;
}

void CRPFace::SetColorInfo(int index, unsigned long color) {
  if (index >= m_vertices.size() || index < 0) {
    return;
  }
}

float CRPFace::GetWCoord(int index) const {
  if (index < m_oows.size() & index >= 0) {
    return m_oows[index];
  }

  return 0.f;
}

void CRPFace::Draw() const {
  if (m_texture) {
    glEnable(GL_TEXTURE_2D);
    m_texture->Bind(GL_TEXTURE_2D);
  }

  glColor4f(1.f, 1.f, 1.f, 1.f);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, m_vertices.data());

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, 0, m_texture_coords.data());

  glDrawElements(m_primType, m_vertices.size(), GL_UNSIGNED_SHORT,
                 m_indices.data());

  glDisableClientState(GL_VERTEX_ARRAY);

  if (m_texture) {
    glDisable(GL_TEXTURE_2D);
  }
}
