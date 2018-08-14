#include "Render/VBO.h"

VBO::VBO() : size_() { glGenBuffers(1, &id_); }

VBO::~VBO() {
  if (id_ != 0) {
    glDeleteBuffers(1, &id_);
    id_ = 0;
  }
}

int VBO::size() const { return size_; }

void VBO::SetData(void* data, int size) {
  size_ = size;
  Bind();
  glBufferData(GL_ARRAY_BUFFER, element_size_ * size, data, GL_DYNAMIC_DRAW);
  Unbind();
}

void VBO::SetSubData(int offset, void* data, int size) {
  Bind();
  glBufferSubData(GL_ARRAY_BUFFER, element_size_ * offset, element_size_ * size,
                  data);
  Unbind();
}

void VBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, id_); }

void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
