// GLEW
#include <GL/glew.h>

void Render() {
  // We clear the screen
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // We define a triangle
  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  // We generate a Vertex Buffer Object (VBO)
  GLuint vbo_handle;                            // The VBO handle
  glGenBuffers(1, &vbo_handle);                 // Generate 1 buffer

  // From this point on, all calls for GL_ARRAY_BUFFER will refer to
  // vbo_handle
  glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

  // This call copies data over to the GL_ARRAY_BUFFER
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  std::string vertex_shader = R"(
#version 330
layout (location = 0) in vec3 pos;

void main() {
  gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}
)";


}
