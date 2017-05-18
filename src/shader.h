#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

namespace opengl_renderer {

class Shader {
  public:
    enum ShaderType {
      VERTEX,
      FRAGMENT
    };

  public:
    void LoadShader(ShaderType type, const std::string& src);
    void LoadShaderFromFile(ShaderType type,
                            const std::string& filepath);

    bool CompileShader(ShaderType type, std::string* error_msg);
    bool LoadAndCompileShaderFromFile(ShaderType type,
                                      const std::string& filepath,
                                      std::string *error_msg);

  private:
   std::string vertex_shader_;
   std::string fragment_shader_;

  private:
   GLuint vertex_shader_handle_;
   GLuint fragment_shader_handle_;
};

}  // opengl_renderer

#endif // SHADER_H
