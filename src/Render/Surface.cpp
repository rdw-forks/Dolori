#include "Surface.h"
#include "../Common/Globals.h"

CSurface::CSurface() { m_textureId = 0; }

CSurface::CSurface(unsigned long w, unsigned long h) {
  m_w = w;
  m_h = h;
}

CSurface::~CSurface() {
  if (m_textureId) glDeleteTextures(1, &m_textureId);
}

bool CSurface::Create(unsigned long w, unsigned long h) {
  m_w = w;
  m_h = h;

  return true;
}

void CSurface::Update(int x, int y, int width, int height, const ILubyte *image,
                      int drawOnlyNoTrans) {
  Create(width, height);

  if (!m_textureId) glGenTextures(1, &m_textureId);
  glBindTexture(GL_TEXTURE_2D, m_textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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

  glLoadIdentity();
  glTranslatef(x, y, 0.f);

  glBindTexture(GL_TEXTURE_2D, m_textureId);
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) return;

  // Render textured quad
  glColor4f(1.f, 1.f, 1.f, 1.f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.f, 1.f);
  glVertex3f(0.f, 0.f, 0.f);
  glTexCoord2f(1.f, 1.f);
  glVertex3f(width, 0.f, 0.f);
  glTexCoord2f(1.f, 0.f);
  glVertex3f(width, height, 0.f);
  glTexCoord2f(0.f, 0.f);
  glVertex3f(0.f, height, 0.f);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}