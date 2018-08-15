#include "Render/FontMgr.h"

#include "Common/debug.h"

CFontMgr::CFontMgr() : loaded_fonts_() {}

CFontMgr::~CFontMgr() { Cleanup(); }

bool CFontMgr::Cleanup() {
  // Close all fonts
  for (auto& elem : loaded_fonts_) {
    TTF_CloseFont(elem.second);
  }

  loaded_fonts_.clear();

  return true;
}

TTF_Font* CFontMgr::GetFont(const std::string& font_name, int font_size) {
  const auto pair = std::make_pair(font_name, font_size);

  const auto result = loaded_fonts_.find(pair);
  if (result != std::cend(loaded_fonts_)) {
    return result->second;
  }

  LOG(debug, "Loading font {} in size {}", font_name, font_size);
  TTF_Font* font = TTF_OpenFont(font_name.c_str(), font_size);
  if (font != nullptr) {
    loaded_fonts_[pair] = font;
  }

  return font;
}
