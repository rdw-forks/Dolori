#ifndef DOLORI_RENDER_SURFACE_H_
#define DOLORI_RENDER_SURFACE_H_

#include <stdint.h>

#include <SDL.h>
#include <il.h>

#include "Render/GlTexture.h"
#include "Render/Motion.h"
#include "Render/SprRes.h"
#include "Render/pixel_format.h"
#include "Render/tag_rect.h"

class CSurface : public CGlTexture {
 public:
  CSurface();
  CSurface(unsigned long, unsigned long);
  CSurface(SDL_Surface*);
  virtual ~CSurface();

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
};

#endif  // DOLORI_RENDER_SURFACE_H_
