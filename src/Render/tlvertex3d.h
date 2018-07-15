#ifndef DOLORI_RENDER_TLVERTEX3D_H_
#define DOLORI_RENDER_TLVERTEX3D_H_

#include <glm/glm.hpp>

#include "Render/color.h"
#include "Render/texcoor.h"

struct TlVertex3d {
  glm::vec3 vertex;
  glm::vec2 texture_coords;
  float oow;
  unsigned long color;
  COLOR argb;
  unsigned long specular;
};

#endif  // DOLORI_RENDER_TLVERTEX3D_H_
