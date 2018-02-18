#include "RPQuadFace.h"

CRPQuadFace::CRPQuadFace() : CRPFace(m_qverts, 4) {
  m_primType = GL_QUADS;
  m_indices = new unsigned short[4]{0, 1, 3, 2};
}

void CRPQuadFace::Draw() const {
  float vertices[4][3] = {{m_verts[0].x, m_verts[0].y, m_verts[0].z},
                          {m_verts[1].x, m_verts[1].y, m_verts[1].z},
                          {m_verts[2].x, m_verts[2].y, m_verts[2].z},
                          {m_verts[3].x, m_verts[3].y, m_verts[3].z}};
  float tex_coords[4][2] = {
      {m_verts[0].texcoord.u, m_verts[0].texcoord.v},
      {m_verts[1].texcoord.u, m_verts[1].texcoord.v},
      {m_verts[2].texcoord.u, m_verts[2].texcoord.v},
      {m_verts[3].texcoord.u, m_verts[3].texcoord.v},
  };

  if (m_texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_texture->texture_id());
  }

  glColor4f(1.f, 1.f, 1.f, 1.f);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);

  // glEnableClientState(GL_INDEX_ARRAY);
  // glIndexPointer(GL_UNSIGNED_SHORT, 0, m_indices);

  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, m_indices);

  glDisableClientState(GL_VERTEX_ARRAY);

  if (m_texture) {
    glDisable(GL_TEXTURE_2D);
  }
}
