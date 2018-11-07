#include "Render/GlProgram.h"

#include <glad/glad.h>

CGlProgram::CGlProgram() : program_id_() {}

CGlProgram::~CGlProgram() { glDeleteProgram(program_id_); }

bool CGlProgram::Init(const std::vector<CGlShader>& shaders) {
  program_id_ = glCreateProgram();
  if (program_id_ == 0) {
    return false;
  }

  // Attach all the shaders
  for (const auto& shader : shaders) {
    glAttachShader(program_id_, shader.id());
  }

  // Link the shaders together
  glLinkProgram(program_id_);

  // Detach all the shaders
  for (const auto& shader : shaders) {
    glDetachShader(program_id_, shader.id());
  }

  GLint status;
  glGetProgramiv(program_id_, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    glDeleteProgram(program_id_);
    program_id_ = 0;
    return false;
  }

  return true;
}

void CGlProgram::Bind() const { glUseProgram(program_id_); }

void CGlProgram::Unbind() const { glUseProgram(0); }

GLuint CGlProgram::GetId() const { return program_id_; }

GLuint CGlProgram::GetUniformLocation(const std::string& uniform_name) const {
  return glGetUniformLocation(program_id_, uniform_name.c_str());
}

GLuint CGlProgram::GetAttributeLocation(
    const std::string& attribute_name) const {
  return glGetAttribLocation(program_id_, attribute_name.c_str());
}
