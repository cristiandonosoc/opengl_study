#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace opengl_renderer {

class Shader {

  private:
   std::string vertex_shader_;
   std::string fragment_shader_;
};

}  // opengl_renderer

#endif // SHADER_H
