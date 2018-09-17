#ifndef DOLORI_RENDER_GLVBO_H_
#define DOLORI_RENDER_GLVBO_H_

#include <glad/glad.h>

class CGlVBO {
 public:
  CGlVBO();
  ~CGlVBO();

  int size() const;

  template <class T>
  inline void SetVertexFormat() {
    element_size_ = sizeof(T);
  }

  void SetData(const void* data, size_t size);
  void SetSubData(int offset, const void* data, int size);
  void Bind();
  void Unbind();

 private:
  size_t element_size_;
  GLuint id_;
  int size_;
};

#endif  // DOLORI_RENDER_GLVBO_H_
