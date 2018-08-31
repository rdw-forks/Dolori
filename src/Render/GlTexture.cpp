#include "Render/GlTexture.h"

CGlTexture::CGlTexture() : binded_target_(0) { glGenTextures(1, &texture_id_); }

CGlTexture::~CGlTexture() {
  if (texture_id_ != 0) {
    glDeleteTextures(1, &texture_id_);
  }
}

void CGlTexture::Bind(GLenum target) {
  glBindTexture(target, texture_id_);
  binded_target_ = target;
}
void CGlTexture::Unbind() {
  if (binded_target_ != 0) {
    glBindTexture(binded_target_, 0);
    binded_target_ = 0;
  }
}

GLuint CGlTexture::texture_id() const { return texture_id_; }
