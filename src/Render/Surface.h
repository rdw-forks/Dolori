#ifndef DOLORI_RENDER_SURFACE_H_
#define DOLORI_RENDER_SURFACE_H_

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <il.h>
#include <stdint.h>
#include "Motion.h"
#include "SprRes.h"
#include "pixel_format.h"
#include "tag_rect.h"

class CSurface {
 public:
  CSurface();
  CSurface(unsigned long, unsigned long);
  CSurface(SDL_Surface*);
  virtual ~CSurface();

  GLuint texture_id() const;
  unsigned long GetWidth();
  unsigned long GetHeight();
  SDL_Surface* GetSDLSurface();
  void Create(unsigned long, unsigned long);
  virtual void Update(int, int, int, int, const ILubyte*, int);
  void UpdateSprite(int x, int y, int width, int height, SPR_IMG* img,
                    const uint32_t* pal);
  void CopyRect(int, int, int, int, SDL_Surface*);
  void BlitBitmap(int x, int y, int w, int h, const ILubyte* bitmap);
  void BlitSurface(int x, int y, CSurface* src, int srcx, int srcy, int width,
                   int height, int xflip, int zoomx, int zoomy);
  void BlitSprite(int x, int y, CSprRes* sprRes, CMotion* curMotion,
                  unsigned int* palette);
  virtual void ClearSurface(SDL_Rect* rect, uint32_t color);
  virtual void DrawSurface(int, int, int, int, unsigned int);
  virtual void DrawSurfaceStretch(int, int, int, int);

 protected:
  void UpdateGlTexture();

 protected:
  unsigned long m_w;
  unsigned long m_h;
  SDL_Surface* m_sdl_surface;
  GLuint m_textureId;
};

#endif  // DOLORI_RENDER_SURFACE_H_
