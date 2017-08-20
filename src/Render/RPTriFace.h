#ifndef DOLORI_RENDER_RPTRIFACE_H_
#define DOLORI_RENDER_RPTRIFACE_H_

#include <GL/glew.h>
#include <SDL_opengl.h>
#include "RPFace.h"
#include "tlvertex3d.h"

class CRPTriFace : public CRPFace {
 public:
  CRPTriFace();

 private:
  struct tlvertex3d m_tverts[0x3];
};

#endif  // DOLORI_RENDER_RPTRIFACE_H_