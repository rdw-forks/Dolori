#include "SurfaceWallpaper.h"

#include <SDL_opengl.h>

CSurfaceWallpaper::CSurfaceWallpaper() {}

CSurfaceWallpaper::CSurfaceWallpaper(unsigned int w, unsigned int h) {
  Create(w, h);
}

CSurfaceWallpaper::~CSurfaceWallpaper() {}
