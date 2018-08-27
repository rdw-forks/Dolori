#include "Render/TextureAtlas.h"

#include <glm/gtc/round.hpp>

#include "Common/Globals.h"

CTextureAtlas::CTextureAtlas()
    : CSurface(), texture_size_(), textures_positions_() {}

void CTextureAtlas::Create(size_t texture_size,
                           const std::vector<char const *> &texture_names) {
  const size_t number_of_textures = texture_names.size();
  const size_t num_of_columns = glm::round(glm::sqrt(number_of_textures));
  const size_t texture_width =
      glm::ceilPowerOfTwo(num_of_columns * texture_size);
  const size_t texture_height = glm::ceilPowerOfTwo(
      (size_t)glm::ceil(glm::sqrt(number_of_textures)) * texture_size);

  CSurface::Create(texture_width, texture_height);
  m_sdl_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, m_w, m_h, 32, 0xff,
                                       0xff00, 0xff0000, 0xff000000);

  for (size_t i = 0; i < number_of_textures; i++) {
    const auto texture = g_TexMgr->GetTexture(texture_names[i], false);
    const int x = (i % num_of_columns) * texture_size;
    const int y = glm::floor(i / num_of_columns) * texture_size;

    textures_positions_[texture_names[i]] =
        glm::vec2(x / (float)texture_width, y / (float)texture_height);

    BlitSurface(x, y, texture.get(), 0, 0, texture->GetWidth(),
                texture->GetHeight(), 0, 1, 1);
  }

  texture_size_ = texture_size;
}

glm::vec2 CTextureAtlas::GetTexturePosition(
    const std::string &texture_name) const {
  auto result = textures_positions_.find(texture_name);
  if (result != std::cend(textures_positions_)) {
    return result->second;
  }

  return {};
}

size_t CTextureAtlas::texture_size() const { return texture_size_; }
