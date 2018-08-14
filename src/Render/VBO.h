#ifndef DOLORI_RENDER_VBO_H_
#define DOLORI_RENDER_VBO_H_

#include <glad/glad.h>

class VBO {
 public:
  VBO();
  ~VBO();

  int size() const;

  template <class T>
  inline void SetVertexFormat() {
    element_size_ = sizeof(T);
  }

  void SetData(void* data, int size);
  void SetSubData(int offset, void* data, int size);
  void Bind();
  void Unbind();

 private:
  size_t element_size_;
  GLuint id_;
  int size_;
};

#endif  // DOLORI_RENDER_VBO_H_
