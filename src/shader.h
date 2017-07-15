#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <memory>
/* #include <GL/glew.h> */
#include <glad/glad.h>

namespace opengl_renderer {

class Shader {
  public:
    static std::unique_ptr<Shader> CreateFromPaths(const std::string& vertex_src,
                                                   const std::string& fragment_src);

  public:
    enum ShaderType {
      VERTEX,
      FRAGMENT
    };

  public:
    ~Shader() {
      DeleteShader(VERTEX);
      DeleteShader(FRAGMENT);
      DeleteProgram();
    }

  public:
    void DeleteShader(ShaderType type);
    void DeleteProgram();
    void LoadShader(ShaderType type, const std::string& filepath,
                    const std::string& src);
    void LoadShaderFromFile(ShaderType type,
                            const std::string& filepath);

    bool CompileShader(ShaderType type, std::string* error_msg);
    bool LoadAndCompileShaderFromFile(ShaderType type,
                                      const std::string& filepath,
                                      std::string *error_msg);
    bool LinkShaders(std::string *error_msg);
    bool UseShader() const;

  public:
    GLuint GetProgramHandle() const { return shader_program_handle_; }

  private:
   std::string vertex_shader_;
   std::string vertex_shader_path_;
   const char *vertex_shader_ptr_;
   std::string fragment_shader_;
   std::string fragment_shader_path_;
   const char *fragment_shader_ptr_;

  private:
   GLuint vertex_shader_handle_ = 0;
   GLuint fragment_shader_handle_ = 0;
   GLuint shader_program_handle_ = 0;

  private:
   std::string path_;
};

}  // opengl_renderer

#endif // SHADER_H
