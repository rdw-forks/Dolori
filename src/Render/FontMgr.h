#ifndef DOLORI_RENDER_FONTMGR_H_
#define DOLORI_RENDER_FONTMGR_H_

#include <SDL_opengl.h>

class CFontMgr {
 public:
  CFontMgr();
  ~CFontMgr();

  bool Init();
  bool Cleanup();
  bool LoadFont(const char*, GLuint);

 private:
};

#endif  // DOLORI_RENDER_FONTMGR_H_
