#ifndef DOLORI_RENDER_SURFACE_H_
#define DOLORI_RENDER_SURFACE_H_

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <il.h>
#include <stdint.h>
#include "pixel_format.h"
#include "tag_rect.h"

class CSurface {
 public:
  CSurface();
  CSurface(unsigned long, unsigned long);
  CSurface(SDL_Surface*);
  virtual ~CSurface();

  unsigned long GetWidth();
  unsigned long GetHeight();
  SDL_Surface* GetSDLSurface();
  bool Create(unsigned long, unsigned long);
  virtual void Update(int, int, int, int, const ILubyte*, int);
  void CopyRect(int, int, int, int, CSurface*);
  virtual void ClearSurface(TAG_RECT*, unsigned long){};
  virtual void DrawSurface(int, int, int, int, unsigned int);
  virtual void DrawSurfaceStretch(int, int, int, int);

 protected:
  void UpdateGlTexture();

 protected:
  unsigned long m_w;
  unsigned long m_h;
  SDL_Surface* m_sdlSurface;
  GLuint m_textureId;
};

#endif  // DOLORI_RENDER_SURFACE_H_
