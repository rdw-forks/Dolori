#include "RPFace.h"
#include <string.h>
#include <iostream>

CRPFace::CRPFace()
    : m_primType(GL_POLYGON),
      m_verts(),
      m_numVerts(),
      m_texture(),
      m_indices(),
      m_numIndices() {}

CRPFace::CRPFace(tlvertex3d* verts, int numVerts) : CRPFace() {
  m_verts = verts;
  m_numVerts = numVerts;
}

CRPFace::~CRPFace() {
  if (m_indices) {
    delete m_indices;
  }
}

void CRPFace::set_texture(CTexture* texture) { m_texture = texture; }

void CRPFace::SetGeomInfo(int index, const tlvertex3d& vert) {
  if (index >= m_numVerts || index < 0) {
    return;
  }

  m_verts[index].x = vert.x;
  m_verts[index].y = vert.y;
  m_verts[index].z = vert.z;
  m_verts[index].oow = vert.oow;
  m_verts[index].texcoord = vert.texcoord;
}

void CRPFace::SetColorInfo(int index, unsigned long color) {
  if (index >= m_numVerts || index < 0) {
    return;
  }

  m_verts[index].color = color;
}

struct tlvertex3d CRPFace::GetVertex(int index) const {
  if (index < m_numVerts & index >= 0) {
    return m_verts[index];
  }

  struct tlvertex3d empty;

  memset(&empty, 0, sizeof(empty));
  return empty;
}

void CRPFace::Draw() const {
  if (m_numVerts == 0) return;

  // glLoadIdentity();
  glBegin(m_primType);

  glColor3f(1.0, 1.0, 1.0);

  uint32_t current_color = 0;
  for (int i = 0; i < m_numVerts; i++) {
    const tlvertex3d v = m_verts[i];
    float r, g, b, a;

    if (current_color != v.color) {
      a = ((v.color >> 24) & 0xFF) / 255.f;
      r = ((v.color >> 16) & 0xFF) / 255.f;
      g = ((v.color >> 8) & 0xFF) / 255.f;
      b = ((v.color) & 0xFF) / 255.f;
      // glColor4f(r, g, b, a);
      current_color = v.color;
    }
    glVertex3f(v.x, v.y, v.z);
  }

  glEnd();
}
