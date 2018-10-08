#include "UI/UIWindow.h"

#include <algorithm>

#include "Common/GetTick.h"
#include "Common/Globals.h"
#include "Common/debug.h"

CUIWindow::CUIWindow()
    : m_parent(),
      m_x(),
      m_y(),
      m_w(),
      m_h(),
      m_isDirty(true),
      m_surface(nullptr),
      m_id(117),
      m_state(),
      m_state_cnt(),
      m_show(true),
      m_trans(255),
      m_transTarget(255),
      m_transTime(GetTick()) {}

CUIWindow::~CUIWindow() {
  for (auto child : m_children) {
    delete child;
  }

  m_children.clear();
}

void CUIWindow::Create(int cx, int cy) {
  OnCreate(cx, cy);
  Resize(cx, cy);
  OnSize(cx, cy);
}

void CUIWindow::Move(int x, int y) {
  m_x = x;
  m_y = y;
}

void CUIWindow::Resize(int cx, int cy) {
  m_w = cx;
  m_h = cy;
  m_surface = std::make_unique<CSurface>(m_w, m_h);
  Invalidate();
}

int CUIWindow::GetX() const { return m_x; }

int CUIWindow::GetY() const { return m_y; }

int CUIWindow::GetHeight() const { return m_h; }

int CUIWindow::GetWidth() const { return m_w; }

void CUIWindow::SetId(size_t id) { m_id = id; }

size_t CUIWindow::GetId() const { return m_id; }

CUIWindow* CUIWindow::GetParent() const { return m_parent; }

void CUIWindow::OnDraw() {}

void CUIWindow::OnCreate(int x, int y) {}

void CUIWindow::OnSize(int width, int height) {}

bool CUIWindow::IsUpdateNeeded() const { return true; }

bool CUIWindow::IsShow() const { return m_show; }

void CUIWindow::SetShow(bool show) { m_show = show; }

void CUIWindow::AddChild(CUIWindow* wnd) {
  wnd->m_parent = this;
  m_children.push_back(wnd);
}

void CUIWindow::RemoveChild(CUIWindow* window) {
  if (window == nullptr) {
    return;
  }

  m_children.erase(
      std::remove_if(std::begin(m_children), std::end(m_children),
                     [window](CUIWindow* child) { return child == window; }));

  delete window;
}

bool CUIWindow::IsChildOf(CUIWindow* wnd) const {
  if (m_parent == nullptr) {
    return false;
  }

  const CUIWindow* parent = m_parent;
  while (parent != wnd) {
    parent = parent->GetParent();
    if (parent == nullptr) {
      return false;
    }
  }

  return true;
}

CUIWindow* CUIWindow::HitTest(int x, int y) {
  CUIWindow* result;

  if (m_show && x >= m_x && x < m_x + m_w && y >= m_y && y < m_y + m_h) {
    if (m_children.empty()) {
      return this;
    }

    for (auto it = std::rbegin(m_children); it != std::rend(m_children); ++it) {
      result = (*it)->HitTest(x - m_x, y - m_y);
      if (result != nullptr && result->IsShow()) {
        return result;
      }
    }

    return this;
  }

  return nullptr;
}

bool CUIWindow::ShouldDoHitTest() { return true; }

void CUIWindow::GetGlobalCoor(int* x, int* y) {
  *x = m_x;
  *y = m_y;

  for (CUIWindow* wnd = m_parent; wnd != nullptr; wnd = wnd->m_parent) {
    *x += wnd->m_x;
    *y += wnd->m_y;
  }
}

void CUIWindow::OnLBtnDown(int x, int y) {}

void CUIWindow::OnLBtnDblClk(int x, int y) {}

void CUIWindow::OnRBtnDown(int x, int y) {}

void CUIWindow::OnRBtnDblClk(int x, int y) {}

void CUIWindow::OnWBtnDown(int x, int y) {}

void CUIWindow::OnLBtnUp(int x, int y) {}

void CUIWindow::OnRBtnUp(int x, int y) {}

void CUIWindow::OnWBtnUp(int x, int y) {}

void CUIWindow::OnMouseShape(int x, int y) {
  // CMode::SetCursorAction(g_modeMgr.m_curMode, 0);
}

void CUIWindow::OnMouseHover(int x, int y) {}

void CUIWindow::OnMouseMove(int x, int y) {}

void CUIWindow::DoDraw(bool blit_to_parent) {
  if (m_isDirty) {
    OnDraw();
    m_isDirty = false;
    blit_to_parent = true;
  }

  for (auto child : m_children) {
    child->DoDraw(blit_to_parent);
  }

  if (blit_to_parent && m_parent != nullptr) {
    m_parent->m_surface->CopyRect(m_x, m_y, m_w, m_h,
                                  m_surface->GetSDLSurface());
  }
}

void CUIWindow::DrawBitmap(int x, int y, const CBitmapRes* bitmap,
                           int drawOnlyNoTrans) {
  if (m_surface != nullptr && bitmap) {
    m_surface->BlitBitmap(x, y, bitmap->GetWidth(), bitmap->GetHeight(),
                          bitmap->GetData());
  }
}

void CUIWindow::DrawBox(int x, int y, int cx, int cy, uint32_t color) {
  SDL_Rect r;

  r.x = x <= 0 ? 0 : x;
  r.y = y <= 0 ? 0 : y;
  if (cx + x >= m_w) {
    r.w = m_w - x;
  } else {
    r.w = cx;
  }
  if (y + cy >= m_h) {
    r.h = m_h - y;
  } else {
    r.h = cy;
  }

  m_surface->ClearSurface(&r, color);
}

void CUIWindow::ClearDC(uint32_t color) {
  if (m_surface == nullptr) {
    return;
  }

  m_surface->ClearSurface(nullptr, color);
}

void CUIWindow::DrawSurface() {
  if (m_surface == nullptr) {
    return;
  }

  m_surface->DrawSurface(m_x, m_y, m_w, m_h, 0xFFFFFFFF);
}

void CUIWindow::InvalidateChildren() {
  Invalidate();

  for (auto child : m_children) {
    if (child->IsUpdateNeeded()) {
      child->InvalidateChildren();
    }
  }
}

void CUIWindow::Invalidate() { m_isDirty = true; }

void CUIWindow::TextOutA(int x, int y, const char* text, size_t textLen,
                         int fontType, int fontHeight, unsigned int colorText) {
  if (text == nullptr) {
    return;
  }

  const std::string font_name = "arial.ttf";
  TTF_Font* font = g_FontMgr->GetFont(font_name, fontHeight);
  if (font == nullptr) {
    LOG(error, "Cannot get font '{}'", font_name);
    return;
  }

  const SDL_Color color = {static_cast<Uint8>((colorText >> 16) & 0xFF),
                           static_cast<Uint8>((colorText >> 8) & 0xFF),
                           static_cast<Uint8>(colorText & 0xFF)};
  SDL_Surface* sdl_surface = TTF_RenderText_Blended(font, text, color);
  if (sdl_surface == nullptr) {
    return;
  }

  if (m_surface != nullptr) {
    m_surface->CopyRect(x, y, sdl_surface->w, sdl_surface->h, sdl_surface);
  } else {
    m_surface = std::make_unique<CSurface>(sdl_surface);
  }
}

void CUIWindow::TextOutUTF8(int x, int y, const char* text, size_t textLen,
                            int fontType, int fontHeight,
                            unsigned int colorText) {
  if (text == nullptr) {
    return;
  }

  const std::string font_name = "arial.ttf";
  TTF_Font* font = g_FontMgr->GetFont(font_name, fontHeight);
  if (font == nullptr) {
    LOG(error, "Cannot get font '{}'", font_name);
    return;
  }

  const SDL_Color color = {static_cast<Uint8>((colorText >> 16) & 0xFF),
                           static_cast<Uint8>((colorText >> 8) & 0xFF),
                           static_cast<Uint8>(colorText & 0xFF)};
  SDL_Surface* sdl_surface = TTF_RenderUTF8_Blended(font, text, color);
  if (sdl_surface != nullptr) {
    if (m_surface != nullptr) {
      m_surface->CopyRect(x, y, sdl_surface->w, sdl_surface->h, sdl_surface);
    } else {
      m_surface = std::make_unique<CSurface>(sdl_surface);
    }
  }
}

void CUIWindow::TextOutWithOutline(int x, int y, const char* text,
                                   size_t textLen, uint32_t colorText,
                                   uint32_t colorOutline, int fontType,
                                   int fontHeight, bool bold) {
  if (text == nullptr) {
    return;
  }

  const std::string font_name = "arial.ttf";
  TTF_Font* font = g_FontMgr->GetFont(font_name, fontHeight);
  if (font == nullptr) {
    LOG(error, "Cannot get font '{}'", font_name);
    return;
  }

  const SDL_Color color = {static_cast<Uint8>((colorText >> 16) & 0xFF),
                           static_cast<Uint8>((colorText >> 8) & 0xFF),
                           static_cast<Uint8>(colorText & 0xFF)};
  const SDL_Color color_outline = {
      static_cast<Uint8>((colorOutline >> 16) & 0xFF),
      static_cast<Uint8>((colorOutline >> 8) & 0xFF),
      static_cast<Uint8>(colorOutline & 0xFF)};

  TTF_SetFontOutline(font, 1);
  SDL_Surface* bg_surface = TTF_RenderText_Blended(font, text, color_outline);
  TTF_SetFontOutline(font, 0);
  SDL_Surface* fg_surface = TTF_RenderText_Blended(font, text, color);
  SDL_Rect rect = {1, 1, fg_surface->w, fg_surface->h};

  /* blit text onto its outline */
  SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
  SDL_BlitSurface(fg_surface, nullptr, bg_surface, &rect);
  SDL_FreeSurface(fg_surface);

  if (m_surface) {
    m_surface->CopyRect(x, y, 40, 20, bg_surface);
  } else {
    m_surface = std::make_unique<CSurface>(bg_surface);
  }
}

void CUIWindow::TextOutWithDecoration(int x, int y, const char* text,
                                      size_t textLen, unsigned int* colorRef,
                                      int fontType, int fontHeight) {
  TextOutA(x, y, text, textLen, fontType, fontHeight, *colorRef);
}

const char* CUIWindow::InterpretColor(const char* color_text,
                                      unsigned int* /*colorRef*/) {
  const char* result;
  // unsigned short v3;

  result = color_text;
  if (color_text != nullptr) {
    if (*color_text == '^') {
      // HIBYTE(v3) = LOBYTE((&hex_table)[color_text[6]]) +
      //             16 * LOBYTE((&hex_table)[color_text[5]]);
      // LOBYTE(v3) = LOBYTE((&hex_table)[color_text[4]]) +
      //             16 * LOBYTE((&hex_table)[color_text[3]]);
      // result = color_text + 7;
      //*colorRef = (unsigned __int8)(LOBYTE((&hex_table)[color_text[2]]) +
      //                              16 * LOBYTE((&hex_table)[color_text[1]]))
      //                              |
      //            (v3 << 8);
    }
  }

  return result;
}

void CUIWindow::OnBeginEdit() {}

void CUIWindow::OnFinishEdit() {}

void* CUIWindow::SendMsg(CUIWindow* /*sender*/, int message, void* /*val1*/,
                         void* /*val2*/, void* /*val3*/, void* /*val4*/) {
  switch (message) {
    case 0:
    case 1:
      if (m_parent != nullptr) {
        m_parent->SendMsg(this, message);
      }
      break;
    default:
      return nullptr;
  }

  return nullptr;
}
