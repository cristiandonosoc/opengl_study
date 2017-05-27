#include "shader.h"
#include "helpers.h"

#include <cstdio>

namespace opengl_renderer {

namespace {

using helpers::FormattedString;

void GetShaderCompileErrorMsg(Shader::ShaderType type,
                              const std::string& path,
                              GLuint handle,
                              std::string *error_msg) {
  GLchar info_log[512];
  glGetShaderInfoLog(handle, 512, NULL, info_log);
  std::string m;
  if (type == Shader::VERTEX) {
    m = FormattedString(100, "[%s] VERTEX COMPILE ERROR: %s", path.c_str(), info_log);
  } else {
    m = FormattedString(100, "[%s] FRAGMENT COMPILE ERROR: %s", path.c_str(), info_log);
  }
  error_msg->assign(m);
}

void GetLinkErrorMsg(GLuint handle, std::string *error_msg) {
  GLchar info_log[512];
  glGetProgramInfoLog(handle, 512, NULL, info_log);
  auto m = FormattedString(100, "SHADER LINKER ERROR: %s", info_log);
  error_msg->assign(m);
}

}  // namespace

void Shader::LoadShader(ShaderType type,
                        const std::string& filepath,
                        const std::string& src) {
  if (type == Shader::VERTEX) {
    vertex_shader_ = src;
    vertex_shader_path_ = filepath;
  } else if (type == Shader::FRAGMENT) {
    fragment_shader_ = src;
    fragment_shader_path_ = filepath;
  } else {
    fprintf(stderr, "Invalid shader type: %d", type);
  }
}

void Shader::LoadShaderFromFile(ShaderType type,
                                const std::string& filepath) {
  std::string src = helpers::LoadFile(filepath);
  LoadShader(type, filepath, src);
}

bool Shader::CompileShader(ShaderType type, std::string* error_msg) {
  GLuint handle = 0;
  const char *src;
  std::string path;
  if (type == Shader::VERTEX) {
    vertex_shader_handle_ = glCreateShader(GL_VERTEX_SHADER);
    handle = vertex_shader_handle_;
    src = vertex_shader_.c_str();
    path = vertex_shader_path_;
  } else if (type == Shader::FRAGMENT) {
    fragment_shader_handle_ = glCreateShader(GL_FRAGMENT_SHADER);
    handle = fragment_shader_handle_;
    src = fragment_shader_.c_str();
    path = fragment_shader_path_;
  }

  glShaderSource(handle, 1, &src, NULL);
  glCompileShader(handle);

  GLint sucess;
  glGetShaderiv(handle, GL_COMPILE_STATUS, &sucess);
  if (!sucess) {
    GetShaderCompileErrorMsg(type, path, handle, error_msg);
    return false;
  }
  return true;
}

bool Shader::LoadAndCompileShaderFromFile(ShaderType type,
                                          const std::string& filepath,
                                          std::string *error_msg) {
  LoadShaderFromFile(type, filepath);
  return CompileShader(type, error_msg);
}

bool Shader::LinkShaders(std::string *error_msg) {
  shader_program_handle_ =  glCreateProgram();
  glAttachShader(shader_program_handle_, vertex_shader_handle_);
  glAttachShader(shader_program_handle_, fragment_shader_handle_);
  glLinkProgram(shader_program_handle_);

  GLint gl_success;
  glGetProgramiv(shader_program_handle_, GL_LINK_STATUS, &gl_success);
  bool success = gl_success != 0;
  if (!success) {
    GetLinkErrorMsg(shader_program_handle_, error_msg);
  }

  // We don't need the shaders anymore
  DeleteShader(Shader::VERTEX);
  DeleteShader(Shader::FRAGMENT);
  return success;
}

void Shader::DeleteShader(ShaderType type) {
  if (type == Shader::VERTEX) {
    glDeleteShader(vertex_shader_handle_);
    vertex_shader_handle_ = 0;
  } else {
    glDeleteShader(fragment_shader_handle_);
    fragment_shader_handle_ = 0;
  }
}

void Shader::DeleteProgram() {
  glDeleteProgram(shader_program_handle_);
}

bool Shader::UseShader() const {
  if (!shader_program_handle_) {
    return false;
  }

  glUseProgram(shader_program_handle_);
  return true;
}

std::unique_ptr<Shader> Shader::CreateFromPaths(
    const std::string& vertex_path,
    const std::string& fragment_path) {
  std::unique_ptr<Shader> shader(new Shader());

  // Vertex shader
  bool success;
  std::string error_msg;
  success = shader->LoadAndCompileShaderFromFile(Shader::VERTEX,
                                                 vertex_path,
                                                 &error_msg);
  if (!success) {
    printf("Error compiling shader: %s\n", error_msg.c_str());
    return nullptr;
  }

  // Fragment Shader
  success = shader->LoadAndCompileShaderFromFile(Shader::FRAGMENT,
                                                 fragment_path,
                                                 &error_msg);
  if (!success) {
    printf("Error compiling shader: %s\n", error_msg.c_str());
    return nullptr;
  }

  // We link the shader
  success = shader->LinkShaders(&error_msg);
  if (!success) {
    printf("Error linking shader: %s\n", error_msg.c_str());
    return nullptr;
  }
  return shader;
}

}  // namespace opengl_renderer
