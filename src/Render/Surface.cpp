#include "Surface.h"
#include "../Common/Globals.h"

CSurface::CSurface() {
  Create(0, 0);
  m_sdlSurface = NULL;
  glGenTextures(1, &m_textureId);
}

CSurface::CSurface(unsigned long w, unsigned long h) {
  Create(w, h);
  m_sdlSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, m_w, m_h, 32, 0xff, 0xff00,
                                      0xff0000, 0xff000000);
  glGenTextures(1, &m_textureId);
}

CSurface::CSurface(SDL_Surface *surface) {
  Create(surface->w, surface->h);
  m_sdlSurface = surface;
  UpdateGlTexture();
}

CSurface::~CSurface() {
  if (m_sdlSurface) SDL_FreeSurface(m_sdlSurface);
  if (m_textureId) glDeleteTextures(1, &m_textureId);
}

unsigned long CSurface::GetWidth() { return m_w; }

unsigned long CSurface::GetHeight() { return m_h; }

SDL_Surface *CSurface::GetSDLSurface() { return m_sdlSurface; }

void CSurface::Create(unsigned long w, unsigned long h) {
  m_w = w;
  m_h = h;
}

void CSurface::Update(int x, int y, int width, int height, const ILubyte *image,
                      int drawOnlyNoTrans) {
  Create(width, height);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
  //             GL_UNSIGNED_BYTE, image);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  if (m_sdlSurface && (m_sdlSurface->w != width || m_sdlSurface->h != height)) {
    SDL_FreeSurface(m_sdlSurface);
    m_sdlSurface = NULL;
  }
  if (!m_sdlSurface)
    m_sdlSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0xff,
                                        0xff00, 0xff0000, 0xff000000);
  SDL_LockSurface(m_sdlSurface);
  memcpy(m_sdlSurface->pixels, image, m_sdlSurface->w * m_sdlSurface->h * 4);
  SDL_UnlockSurface(m_sdlSurface);
  UpdateGlTexture();
}

void CSurface::CopyRect(int x, int y, int w, int h, SDL_Surface *src) {
  if (!src) return;

  if (m_sdlSurface) {
    SDL_Rect dst_rect;
    dst_rect.x = x;
    dst_rect.y = y;
    dst_rect.w = w;
    dst_rect.h = h;
    SDL_BlitSurface(src, NULL, m_sdlSurface, &dst_rect);
    UpdateGlTexture();
  }
}

void CSurface::CopyBitmap(int x, int y, int w, int h, const ILubyte *bitmap) {
  if (!bitmap) return;

  if (m_sdlSurface) {
    SDL_Surface *surface;

    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0xff, 0xff00,
                                   0xff0000, 0xff000000);
    SDL_LockSurface(surface);
    memcpy(surface->pixels, bitmap, surface->w * surface->h * 4);
    SDL_UnlockSurface(surface);
    CopyRect(x, y, w, h, surface);
    SDL_FreeSurface(surface);
  }
}

void CSurface::ClearSurface(SDL_Rect *rect, uint32_t color)
{
  if (m_sdlSurface)
    SDL_FillRect(m_sdlSurface, rect, color);
}

void CSurface::DrawSurface(int x, int y, int width, int height,
                           unsigned int color) {
  int right, left, top, bottom;
  int s_x;
  int s_y;

  s_x = x;
  right = width;
  left = 0;
  top = 0;
  bottom = height;
  if (x + width > g_3dDevice->GetWidth()) right = g_3dDevice->GetWidth() - x;
  s_y = y;
  if (y + height > g_3dDevice->GetHeight())
    bottom = g_3dDevice->GetHeight() - y;
  if (x < 0) {
    left = -x;
    s_x = 0;
  }
  if (y < 0) {
    top = -y;
    s_y = 0;
  }
  if (right > left && bottom > top)
    DrawSurfaceStretch(s_x, s_y, right, bottom);
}

void CSurface::DrawSurfaceStretch(int x, int y, int width, int height) {
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(x, y, 0.f);

  glBindTexture(GL_TEXTURE_2D, m_textureId);
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) return;

  // Render textured quad
  glColor4f(1.f, 1.f, 1.f, 1.f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.f, 0.f);
  glVertex3f(0.f, 0.f, 0.f);
  glTexCoord2f(1.f, 0.f);
  glVertex3f(width, 0.f, 0.f);
  glTexCoord2f(1.f, 1.f);
  glVertex3f(width, height, 0.f);
  glTexCoord2f(0.f, 1.f);
  glVertex3f(0.f, height, 0.f);
  glEnd();

  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
}

void CSurface::UpdateGlTexture() {
  glBindTexture(GL_TEXTURE_2D, m_textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_sdlSurface->w, m_sdlSurface->h, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, m_sdlSurface->pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
