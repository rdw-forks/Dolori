#include "UIWindow.h"
#include <SDL_ttf.h>
#include "../Common/GetTick.h"

CUIWindow::CUIWindow() {
  m_x = 0;
  m_y = 0;
  m_w = 0;
  m_h = 0;
  m_parent = NULL;
  m_state = 0;
  m_stateCnt = 0;
  m_surface = NULL;
  m_isDirty = true;
  m_id = 117;
  m_show = true;
  m_trans = 255;
  m_transTarget = 255;
  m_transTime = GetTick();
}

CUIWindow::~CUIWindow() {}

void CUIWindow::Create(int cx, int cy) {
  if (m_surface) delete m_surface;
  m_surface = new CSurface();
  m_w = cx;
  m_h = cy;
  OnCreate(cx, cy);
  OnSize(cx, cy);
}

void CUIWindow::Move(int x, int y) {
  m_x = x;
  m_y = y;
}

void CUIWindow::Resize(int cx, int cy) {
  m_w = cx;
  m_h = cy;
}

int CUIWindow::GetX() { return m_x; }

int CUIWindow::GetY() { return m_y; }

int CUIWindow::GetHeight() { return m_h; }

int CUIWindow::GetWidth() { return m_w; }

void CUIWindow::SetId(int id) { m_id = id; }

int CUIWindow::GetId() { return m_id; }

CUIWindow* CUIWindow::GetParent() { return m_parent; }

void CUIWindow::OnDraw() {}

void CUIWindow::OnCreate(int, int) {}

void CUIWindow::OnSize(int, int) {}

bool CUIWindow::IsUpdateNeeded() { return true; }

bool CUIWindow::IsShow() { return m_show; }

void CUIWindow::SetShow(bool show) { m_show = show; }

void CUIWindow::AddChild(CUIWindow* wnd) {
  wnd->m_parent = this;
  m_children.push_back(wnd);
}

void CUIWindow::DoDraw(bool blit_to_parent) {
  if (m_isDirty) {
    OnDraw();
    m_isDirty = false;
    blit_to_parent = true;
  }

  for (auto it = m_children.begin(); it != m_children.end(); ++it)
    (*it)->DoDraw(blit_to_parent);

  if (blit_to_parent && m_parent) {
    m_parent->m_surface->CopyRect(m_x, m_y, m_w, m_h, m_surface);
  }
}

void CUIWindow::DrawBitmap(int x, int y, CBitmapRes* bitmap,
                           int drawOnlyNoTrans) {
  if (m_surface && bitmap) {
    m_surface->Update(x, y, bitmap->GetWidth(), bitmap->GetHeight(),
                      bitmap->GetData(), drawOnlyNoTrans);
  }
}

void CUIWindow::DrawSurface() {
  if (m_surface) {
    m_surface->DrawSurface(m_x, m_y, m_w, m_h, 0xFFFFFFFF);
  }
}

void CUIWindow::InvalidateChildren() {
  m_isDirty = true;
  for (auto it = m_children.begin(); it != m_children.end(); ++it) {
    if ((*it)->IsUpdateNeeded()) (*it)->InvalidateChildren();
  }
}

void CUIWindow::TextOutA(int x, int y, const char* text, int textLen,
                         int fontType, int fontHeight, unsigned int colorText) {
  TTF_Font* font = TTF_OpenFont("arial.ttf", fontHeight);
  SDL_Color color = {(colorText >> 16) & 0xFF, (colorText >> 8) & 0xFF,
                     colorText & 0xFF};
  SDL_Surface* sdl_surface = TTF_RenderText_Blended(font, text, color);
  if (m_surface) {
    CSurface text_surface(sdl_surface);
    m_surface->CopyRect(x, y, 40, 20, &text_surface);
  } else {
    m_surface = new CSurface(sdl_surface);
  }

  TTF_CloseFont(font);
}

void CUIWindow::TextOutWithOutline(int x, int y, const char* text, int textLen,
                                   uint32_t colorText, uint32_t colorOutline,
                                   int fontType, int fontHeight, bool bold) {
  SDL_Color color_outline = {(colorOutline >> 16) & 0xFF,
                             (colorOutline >> 8) & 0xFF, colorOutline & 0xFF};
  SDL_Color color = {(colorText >> 16) & 0xFF, (colorText >> 8) & 0xFF,
                     colorText & 0xFF};
  TTF_Font* font = TTF_OpenFont("arial.ttf", fontHeight);

  TTF_SetFontOutline(font, 1);
  SDL_Surface* bg_surface =
      TTF_RenderText_Blended(font, text, color_outline);
  TTF_SetFontOutline(font, 0);
  SDL_Surface* fg_surface = TTF_RenderText_Blended(font, text, color);
  SDL_Rect rect = {1, 1, fg_surface->w, fg_surface->h};

  /* blit text onto its outline */
  SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
  SDL_BlitSurface(fg_surface, NULL, bg_surface, &rect);
  SDL_FreeSurface(fg_surface);

  if (m_surface) {
    CSurface text_surface(bg_surface);
    m_surface->CopyRect(x, y, 40, 20, &text_surface);
  } else {
    m_surface = new CSurface(bg_surface);
  }

  TTF_CloseFont(font);
}
