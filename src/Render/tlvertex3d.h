#ifndef DOLORI_RENDER_TLVERTEX3D_H_
#define DOLORI_RENDER_TLVERTEX3D_H_

#include "color.h"
#include "texcoor.h"

struct tlvertex3d {
  float x;
  float y;
  float z;
  float oow;
  unsigned long color;
  struct COLOR argb;
  unsigned long specular;
  float tu;
  float tv;
  struct TEXCOOR coord;
};

#endif  // DOLORI_RENDER_TLVERTEX3D_H_