#ifndef DOLORI_RENDER_GLPROGRAM_H_
#define DOLORI_RENDER_GLPROGRAM_H_

#include <vector>

#include "Render/GlShader.h"

class CGlProgram {
 public:
  CGlProgram();
  ~CGlProgram();

  bool Init(const std::vector<CGlShader>& shaders);
  void Bind() const;
  void Unbind() const;
  GLuint GetUniformLocation(const std::string& uniform_name) const;
  GLuint GetAttributeLocation(const std::string& attribute_name) const;

 private:
  // Disable object copy
  CGlProgram(const CGlProgram&);
  const CGlProgram& operator=(const CGlProgram&);

 private:
  GLuint program_id_;
};

#endif  // DOLORI_RENDER_GLPROGRAM_H_
