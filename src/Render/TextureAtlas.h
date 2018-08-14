#ifndef DOLORI_RENDER_TEXTURE_ATLAS_H_
#define DOLORI_RENDER_TEXTURE_ATLAS_H_

#include <map>
#include <vector>

#include <glm/glm.hpp>

#include "Render/Surface.h"

class CTextureAtlas : public CSurface {
 public:
  CTextureAtlas();

  void Create(size_t texture_size,
              const std::vector<char const *> &texture_names);
  glm::vec2 GetTexturePosition(const std::string &texture_name) const;
  size_t texture_size() const;

 private:
  size_t texture_size_;
  std::map<std::string, glm::vec2> textures_positions_;
};

#endif  // DOLORI_RENDER_TEXTURE_ATLAS_H_
