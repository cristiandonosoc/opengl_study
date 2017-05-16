#include "shader.h"

#include <cstdio>


namespace opengl_renderer {

void Shader::LoadShader(ShaderType type, const std::string& src) {
  if (type == Shader::VERTEX) {
    vertex_shader_ = src;
  } else if (type == Shader::FRAGMENT) {
    fragment_shader_ = src;
  } else {
    fprintf(stderr, "Invalid shader type: %d", type);
  }
}

bool Shader::CompileShader(ShaderType type, std::string* error_msg) {
  GLuint handle;
  const char *src;
  if (type == Shader::VERTEX) {
    vertex_shader_handle_ = glCreateShader(GL_VERTEX_SHADER);
    handle = vertex_shader_handle_;
    src = vertex_shader_.c_str();
  } else if (type == Shader::FRAGMENT) {
    fragment_shader_handle_ = glCreateShader(GL_FRAGMENT_SHADER);
    handle = fragment_shader_handle_;
    src = fragment_shader_.c_str();
  }

  glShaderSource(handle, 1, &src, NULL);
  glCompileShader(handle);

  GLint sucess;
  GLchar info_log[512];
  glGetShaderiv(handle, GL_COMPILE_STATUS, &sucess);
  if (!sucess) {
    glGetShaderInfoLog(handle, 512, NULL, info_log);
    error_msg->assign(info_log);
    return false;
  }
  return true;
}

}  // namespace opengl_renderer
