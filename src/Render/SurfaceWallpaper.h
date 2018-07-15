#ifndef DOLORI_RENDER_SURFACEWALLPAPER_H_
#define DOLORI_RENDER_SURFACEWALLPAPER_H_

#include "Render/Surface.h"

class CSurfaceWallpaper : public CSurface {
 public:
  CSurfaceWallpaper();
  CSurfaceWallpaper(unsigned int, unsigned int);
  ~CSurfaceWallpaper();
};

// class CSurfaceWallpaper {
//	CSurface, offset = 0x0
//
//		public void CSurfaceWallpaper(const class CSurfaceWallpaper &)
//		public void CSurfaceWallpaper::CSurfaceWallpaper(unsigned long,
// unsigned long) 		public void CSurfaceWallpaper::Update(int, int,
// int, int, unsigned long *, unsigned char, int) 		public class
// CSurfaceWallpaper & operator=(const class CSurfaceWallpaper &)
//		public void CSurfaceWallpaper::~CSurfaceWallpaper()
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_SURFACEWALLPAPER_H_
