#ifndef DOLORI_RENDER_RPFACE_H_
#define DOLORI_RENDER_RPFACE_H_

#include <GL/glew.h>
#include <SDL_opengl.h>
#include "Texture.h"
#include "tlvertex3d.h"

class CRPFace {
 public:
  virtual ~CRPFace();

  void set_texture(CTexture* texture);

  void SetGeomInfo(int, const struct tlvertex3d&);
  void SetColorInfo(int, unsigned long);
  struct tlvertex3d GetVertex(int index) const;
  virtual void Draw() const;
  // public void RPFace::SetGeomInfo(int, const struct vector4d &)
  // public void RPFace::SetGeomInfo(int, const struct tlvertex3d &)
  // public void RPFace::InitSpecular()

 protected:
  CRPFace();
  CRPFace(tlvertex3d*, int);

 protected:
  GLenum m_primType;
  tlvertex3d* m_verts;
  int m_numVerts;
  CTexture* m_texture;
  unsigned short* m_indices;
  unsigned long m_numIndices;
  // unsigned long srcAlphaMode;
  // unsigned long destAlphaMode;
  // unsigned long mtPreset;
};

#endif  // DOLORI_RENDER_RPFACE_H_