#include "Surface.h"
#include "../Common/Globals.h"

CSurface::CSurface() {
  m_sdlSurface = NULL;
  glGenTextures(1, &m_textureId);
}

CSurface::CSurface(unsigned long w, unsigned long h) {
  m_w = w;
  m_h = h;
}

CSurface::CSurface(SDL_Surface *surface) {
  m_sdlSurface = surface;
  Create(m_sdlSurface->w, m_sdlSurface->h);
  UpdateGlTexture();
}

CSurface::~CSurface() {
  if (m_sdlSurface) SDL_FreeSurface(m_sdlSurface);
  if (m_textureId) glDeleteTextures(1, &m_textureId);
}

unsigned long CSurface::GetWidth() { return m_w; }

unsigned long CSurface::GetHeight() { return m_h; }

SDL_Surface *CSurface::GetSDLSurface() { return m_sdlSurface; }

bool CSurface::Create(unsigned long w, unsigned long h) {
  m_w = w;
  m_h = h;

  return true;
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

void CSurface::CopyRect(int x, int y, int w, int h, CSurface *src) {
  if (!src) return;

  SDL_Rect dst_rect;
  dst_rect.x = x;
  dst_rect.y = y;
  dst_rect.w = w;
  dst_rect.h = h;
  SDL_BlitSurface(src->GetSDLSurface(), NULL, m_sdlSurface, &dst_rect);
  UpdateGlTexture();
}

void CSurface::DrawSurface(int x, int y, int width, int height,
                           unsigned int color) {
  tagRECT r;
  int s_x;
  int s_y;

  s_x = x;
  r.right = width;
  r.left = 0;
  r.top = 0;
  r.bottom = height;
  if (x + width > g_3dDevice->GetWidth()) r.right = g_3dDevice->GetWidth() - x;
  s_y = y;
  if (y + height > g_3dDevice->GetHeight())
    r.bottom = g_3dDevice->GetHeight() - y;
  if (x < 0) {
    r.left = -x;
    s_x = 0;
  }
  if (y < 0) {
    r.top = -y;
    s_y = 0;
  }
  if (r.right > r.left && r.bottom > r.top)
    DrawSurfaceStretch(s_x, s_y, r.right, r.bottom);
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
