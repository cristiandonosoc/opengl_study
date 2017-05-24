// GLEW
#include <GL/glew.h>

#include <string>

#include "shader.h"

namespace opengl_renderer {

void SetupRender() {




}

void Render() {
  // We clear the screen
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

}  // namespace opengl_renderer
