#ifndef DOLORI_RENDER_RPQUADFACE_H_
#define DOLORI_RENDER_RPQUADFACE_H_

#include <GL/glew.h>
#include <SDL_opengl.h>
#include "RPFace.h"
#include "tlvertex3d.h"

class CRPQuadFace : public CRPFace {
 public:
  CRPQuadFace();

 private:
  struct tlvertex3d m_qverts[0x4];
};

#endif  // DOLORI_RENDER_RPQUADFACE_H_