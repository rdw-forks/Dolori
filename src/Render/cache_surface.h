#ifndef DOLORI_RENDER_CACHE_SURFACE_H_
#define DOLORI_RENDER_CACHE_SURFACE_H_

#include <vector>

#include "Render/Texture.h"
#include "Render/cache_info.h"

// typedef struct CACHE_SURFACE {
//  CTexture* tex;
//  int w;
//  int h;
//  int tex_width;
//  int tex_height;
//  std::vector<CACHE_INFO> info;
//  int is_locked;
//  unsigned long last_time;
//} CACHE_SURFACE;

typedef struct CACHE_SURFACE {
  size_t id;
  size_t pal_id;
  CSurface* tex;
  unsigned long last_time;
} SurfaceCache;

#endif  // DOLORI_RENDER_CACHE_SURFACE_H_
