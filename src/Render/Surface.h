#ifndef DOLORI_RENDER_SURFACE_H_
#define DOLORI_RENDER_SURFACE_H_

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <il.h>
#include <stdint.h>
#include "../Common/pixel_format.h"
#include "tag_rect.h"

class CSurface {
 public:
  CSurface();
  CSurface(unsigned long, unsigned long);
  virtual ~CSurface();

  bool Create(unsigned long, unsigned long);
  virtual void Update(int, int, const ILubyte*);
  virtual void ClearSurface(TAG_RECT* rect, unsigned long color){};
  virtual void DrawSurface(int x, int y, int width, int height,
                           unsigned long color){};
  virtual void DrawSurfaceStretch(int, int, int, int);

 protected:
  unsigned long m_w;
  unsigned long m_h;
  // PIXEL_FORMAT m_pf;
  GLuint m_textureId;
};

#endif  // DOLORI_RENDER_SURFACE_H_
