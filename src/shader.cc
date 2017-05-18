#include "shader.h"
#include "helpers.h"

#include <cstdio>

namespace opengl_renderer {

namespace {

using helpers::FormattedString;

void GetShaderCompileErrorMsg(Shader::ShaderType type,
                              GLuint handle,
                              std::string *error_msg) {
  GLchar info_log[512];
  glGetShaderInfoLog(handle, 512, NULL, info_log);
  std::string m;
  if (type == Shader::VERTEX) {
    m = FormattedString(100, "VERTEX COMPILE ERROR: %s", info_log);
  } else {
    m = FormattedString(100, "VERTEX COMPILE ERROR: %s", info_log);
  }
  error_msg->assign(m);
}

}  // namespace

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
  GLuint handle = 0;
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
  glGetShaderiv(handle, GL_COMPILE_STATUS, &sucess);
  if (!sucess) {
    GetShaderCompileErrorMsg(type, handle, error_msg);
    return false;
  }
  return true;
}

}  // namespace opengl_renderer
