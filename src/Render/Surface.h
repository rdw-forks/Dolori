#ifndef DOLORI_RENDER_SURFACE_H_
#define DOLORI_RENDER_SURFACE_H_

#include <stdint.h>

#include <SDL.h>
#include <il.h>

#include "Files/SprRes.h"
#include "Render/GlTexture.h"
#include "Render/Motion.h"
#include "Render/pixel_format.h"

class CSurface : public CGlTexture {
 public:
  CSurface();
  explicit CSurface(SDL_Surface*);
  CSurface(unsigned long, unsigned long);
  ~CSurface();

  virtual void ClearSurface(SDL_Rect* rect, uint32_t color);
  virtual void DrawSurface(int, int, int, int, unsigned int);
  virtual void DrawSurfaceStretch(int, int, int, int);
  virtual void Update(int, int, int, int, const ILubyte*, int);

  unsigned long GetWidth() const;
  unsigned long GetHeight() const;
  SDL_Surface* GetSDLSurface() const;
  SDL_Surface* GetSDLSurfaceXFlipped();

  void Create(unsigned long, unsigned long);
  void UpdateSprite(int x, int y, int width, int height, const SprImg* img,
                    const uint32_t* pal);
  void CopyRect(int, int, int, int, SDL_Surface*);
  void BlitBitmap(int x, int y, int w, int h, const ILubyte* bitmap);
  void BlitSurface(int x, int y, CSurface* src, int srcx, int srcy, int width,
                   int height, int xflip, float zoomx, float zoomy);
  void BlitSprite(int x, int y, CSprRes* sprRes, CMotion* curMotion,
                  uint32_t* palette);

 protected:
  void UpdateGlTexture();

 protected:
  unsigned long m_w;
  unsigned long m_h;
  SDL_Surface* m_sdl_surface;
  bool m_update_xflipped_needed;
  SDL_Surface* m_sdl_surface_xflipped;
};

#endif  // DOLORI_RENDER_SURFACE_H_
