#ifndef DOLORI_RENDER_GND_CELL_H_
#define DOLORI_RENDER_GND_CELL_H_

#include "../Common/Vector3d.h"

typedef struct GND_CELL {
  float h[0x4];
  CVector3d watervert[0x4];
  struct CGndSurface* top;
  struct CGndSurface* right;
  struct CGndSurface* front;
  int renderSignature;
  unsigned char cellColor[0x3];
} GND_CELL;

#endif  // DOLORI_RENDER_GND_CELL_H_