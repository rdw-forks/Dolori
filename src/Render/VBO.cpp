#include "Render/VBO.h"

CGlVBO::CGlVBO() : size_() { glGenBuffers(1, &id_); }

CGlVBO::~CGlVBO() {
  if (id_ != 0) {
    glDeleteBuffers(1, &id_);
    id_ = 0;
  }
}

int CGlVBO::size() const { return size_; }

void CGlVBO::SetData(const void* data, size_t size) {
  size_ = size;
  Bind();
  glBufferData(GL_ARRAY_BUFFER, element_size_ * size, data, GL_DYNAMIC_DRAW);
  Unbind();
}

void CGlVBO::SetSubData(int offset, const void* data, int size) {
  Bind();
  glBufferSubData(GL_ARRAY_BUFFER, element_size_ * offset, element_size_ * size,
                  data);
  Unbind();
}

void CGlVBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, id_); }

void CGlVBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
