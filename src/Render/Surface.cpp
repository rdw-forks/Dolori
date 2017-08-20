#include "Surface.h"

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

void CSurface::Update(int width, int height, const ILubyte* image) {
  Create(width, height);

  glGenTextures(1, &m_textureId);
  glBindTexture(GL_TEXTURE_2D, m_textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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