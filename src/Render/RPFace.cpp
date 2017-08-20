#include "RPFace.h"
#include <iostream>

CRPFace::CRPFace() {}

CRPFace::CRPFace(struct tlvertex3d* verts, int numVerts) {
  m_verts = verts;
  m_numVerts = numVerts;
  m_numIndices = 0;
}

void CRPFace::SetGeomInfo(int index, const struct tlvertex3d& vert) {
  if (index < m_numVerts) {
    m_verts[index].x = vert.x;
    m_verts[index].y = vert.y;
    m_verts[index].z = vert.z;
    m_verts[index].oow = vert.oow;
  }
}

void CRPFace::SetColorInfo(int index, unsigned long color) {
	if (index < m_numVerts) {
		m_verts[index].color = color;
	}
}

struct tlvertex3d CRPFace::GetVertex(int index) {
	if (index < m_numVerts) {
		return m_verts[index];
	}
	else {
		struct tlvertex3d empty;
		return empty;
	}
}

void CRPFace::DrawPri() {
  if (m_numVerts) {
    if (m_numIndices) {
    } else {
      unsigned long current_color = 0;

      glBegin(m_primType);
      for (int i = 0; i < m_numVerts; i++) {
        tlvertex3d v = m_verts[i];
        float r, g, b, a;

		if (current_color != v.color) {
			a = ((v.color >> 24) & 0xFF) / 255.f;
			r = ((v.color >> 16) & 0xFF) / 255.f;
			g = ((v.color >> 8) & 0xFF) / 255.f;
			b = ((v.color) & 0xFF) / 255.f;
			glColor4f(r, g, b, a);
			current_color = v.color;
		}
        glVertex3f(v.x, v.y, v.z);
      }
      glEnd();
    }
  }
}