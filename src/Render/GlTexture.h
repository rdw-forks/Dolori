#ifndef DOLORI_RENDER_GLTEXTURE_H_
#define DOLORI_RENDER_GLTEXTURE_H_

#include <glad/glad.h>

class CGlTexture {
 public:
  CGlTexture();
  ~CGlTexture();

  void Bind(GLenum target);
  void Unbind();

  GLuint id() const;

 private:
  GLuint texture_id_;
  GLenum binded_target_;
};

#endif  // DOLORI_RENDER_GLTEXTURE_H_
