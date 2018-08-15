#ifndef DOLORI_RENDER_FONTMGR_H_
#define DOLORI_RENDER_FONTMGR_H_

#include <map>
#include <string>

#include <SDL_ttf.h>

class CFontMgr {
 public:
  CFontMgr();
  ~CFontMgr();

  bool Cleanup();
  TTF_Font* GetFont(const std::string& font_name, int font_size);

 private:
  std::map<std::pair<std::string, int>, TTF_Font*> loaded_fonts_;
};

#endif  // DOLORI_RENDER_FONTMGR_H_
