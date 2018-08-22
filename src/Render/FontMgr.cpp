#include "Render/FontMgr.h"

#include "Common/debug.h"

CFontMgr::CFontMgr() : m_loaded_fonts(), m_font_folder() {}

CFontMgr::~CFontMgr() { Cleanup(); }

void CFontMgr::SetFontFolder(const std::string& font_folder) {
  m_font_folder = font_folder;
}

bool CFontMgr::Cleanup() {
  // Close all fonts
  for (auto& elem : m_loaded_fonts) {
    TTF_CloseFont(elem.second);
  }

  m_loaded_fonts.clear();

  return true;
}

TTF_Font* CFontMgr::GetFont(const std::string& font_name, int font_size) {
  const auto pair = std::make_pair(font_name, font_size);

  const auto result = m_loaded_fonts.find(pair);
  if (result != std::cend(m_loaded_fonts)) {
    return result->second;
  }

  LOG(debug, "Loading font {} in size {}", font_name, font_size);
  TTF_Font* font = TTF_OpenFont((m_font_folder + font_name).c_str(), font_size);
  if (font != nullptr) {
    m_loaded_fonts[pair] = font;
  }

  return font;
}
