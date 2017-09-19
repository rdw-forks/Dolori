#ifndef DOLORI_RENDER_VIEW_SPRITE_H_
#define DOLORI_RENDER_VIEW_SPRITE_H_

#include <string>

struct VIEW_SPRITE {
  int x;
  int y;
  std::string act_name[0x5];
  std::string spr_name[0x5];
  std::string imf_name;
  int head_palette;
  int body_palette;
  std::string head_palette_name;
  std::string body_palette_name;
  int base_action;
  int cur_action;
  int cur_motion;
};

#endif  // DOLORI_RENDER_VIEW_SPRITE_H_