#ifndef DOLORI_RENDER_VIEW_SPRITE_H_
#define DOLORI_RENDER_VIEW_SPRITE_H_

#include <string>

#define VIEW_SPRITE_LAYERS_COUNT 5

struct VIEW_SPRITE {
  int x;
  int y;
  std::string act_name[VIEW_SPRITE_LAYERS_COUNT];
  std::string spr_name[VIEW_SPRITE_LAYERS_COUNT];
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
