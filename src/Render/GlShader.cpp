#include "Render/GlShader.h"

#include <iostream>
#include <vector>

CGlShader::CGlShader() {}

CGlShader::~CGlShader() {}

bool CGlShader::Init(const std::string& shader_code, GLenum shader_type) {
  // create the shader object
  shader_id_ = glCreateShader(shader_type);
  if (shader_id_ == 0) {
    return false;
  }

  // set the source code
  const char* code = shader_code.c_str();
  glShaderSource(shader_id_, 1, (const GLchar**)&code, nullptr);
  glCompileShader(shader_id_);

  GLint status;
  glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    GLint max_length = 0;
    glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &max_length);

    // max_length includes the NULL character
    std::vector<GLchar> error_log(max_length);
    glGetShaderInfoLog(shader_id_, max_length, &max_length, &error_log[0]);

    std::cout << "Shader compilation failed:" << std::endl;
    std::cout << error_log.data() << std::endl;

    glDeleteShader(shader_id_);
    shader_id_ = 0;
    return false;
  }

  return true;
}

GLuint CGlShader::id() const { return shader_id_; }
