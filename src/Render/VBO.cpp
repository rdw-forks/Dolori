#include "Render/VBO.h"

GlVBO::GlVBO() : size_() { glGenBuffers(1, &id_); }

GlVBO::~GlVBO() {
  if (id_ != 0) {
    glDeleteBuffers(1, &id_);
    id_ = 0;
  }
}

int GlVBO::size() const { return size_; }

void GlVBO::SetData(const void* data, int size) {
  size_ = size;
  Bind();
  glBufferData(GL_ARRAY_BUFFER, element_size_ * size, data, GL_DYNAMIC_DRAW);
  Unbind();
}

void GlVBO::SetSubData(int offset, const void* data, int size) {
  Bind();
  glBufferSubData(GL_ARRAY_BUFFER, element_size_ * offset, element_size_ * size,
                  data);
  Unbind();
}

void GlVBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, id_); }

void GlVBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
