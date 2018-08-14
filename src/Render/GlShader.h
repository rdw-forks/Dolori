#ifndef DOLORI_RENDER_GLSHADER_H_
#define DOLORI_RENDER_GLSHADER_H_

#include <string>

#include <glad/glad.h>

class CGlShader {
 public:
  CGlShader();
  ~CGlShader();

  bool Init(const std::string& shader_code, GLenum shader_type);

  GLuint id() const;

 private:
  GLuint shader_id_;
};

#endif  // DOLORI_RENDER_GLSHADER_H_
