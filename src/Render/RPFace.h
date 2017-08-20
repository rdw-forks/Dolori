#ifndef DOLORI_RENDER_RPFACE_H_
#define DOLORI_RENDER_RPFACE_H_

#include <GL/glew.h>
#include <SDL_opengl.h>
#include "tlvertex3d.h"

class CRPFace {
 public:
  CRPFace();
  CRPFace(struct tlvertex3d*, int);
  void SetGeomInfo(int, const struct tlvertex3d &);
  void SetColorInfo(int, unsigned long);
  struct tlvertex3d GetVertex(int index);
  void DrawPri();
  // public void RPFace::SetGeomInfo(int, const struct vector4d &)
  // public void RPFace::SetGeomInfo(int, const struct tlvertex3d &)
  // public void RPFace::InitSpecular()

 protected:
  struct tlvertex3d* m_verts;
  int m_numVerts;
  class CTexture* tex;
  unsigned short* indices;
  unsigned long m_numIndices;
  unsigned long srcAlphaMode;
  unsigned long destAlphaMode;
  unsigned long mtPreset;
  GLenum m_primType;
};

#endif  // DOLORI_RENDER_RPFACE_H_