// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <cstdio>

#include "render.h"
#include "shader.h"
#include "helpers.h"

using opengl_renderer::Shader;
using opengl_renderer::helpers::LoadFile;

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);
  if (window == nullptr) {
    printf("Failed to create GLFW window\n");
    return 1;
  }
  glfwMakeContextCurrent(window);

  // GLEW Initialization
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    return 1;
  }

  int width;
  int height;

  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  glfwSetKeyCallback(window, KeyCallback);

  opengl_renderer::SetupRender();

  // We create the shader that we're going to use
  std::unique_ptr<Shader> shader_ptr = Shader::CreateFromPaths("shaders/simple.vert",
                                                               "shaders/simple.frag");
  // We generate a Vertex Buffer Object (VBO)
  GLuint vbo_handle;              // The VBO handle
  glGenBuffers(1, &vbo_handle);   // Generate 1 buffer

  // We create our vertex array objects
  GLuint vao_handle;
  glCreateVertexArrays(1, &vao_handle);

	// We create an Element Buffer Object
  GLuint ebo_handle;
  glGenBuffers(1, &ebo_handle);

  // We store the information we need to interpret the points
  glBindVertexArray(vao_handle);  // This VAO is now active
  {
    // We send over the vertices
		GLfloat vertices[] = {
				 0.5f,  0.5f, 0.0f,  // Top Right
				 0.5f, -0.5f, 0.0f,  // Bottom Right
				-0.5f, -0.5f, 0.0f,  // Bottom Left
				-0.5f,  0.5f, 0.0f   // Top Left
		};
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);  // This VBO is active for GL_ARRAY_BUFFER
    // We sent this information to the current binded GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // We set out vertex attrib pointer (how to interpret GL_ARRAY_BUFFER)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // We send over the vertex indices
		GLuint indices[] = {    // Note that we start from 0!
				0, 1, 3,            // First Triangle
				1, 2, 3             // Second Triangle
		};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  }
  // We undind the buffer array
  glBindVertexArray(0);

  // DEBUG
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // "Game" loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_ptr->UseShader();
    // We bind the attributes for this draw call
    glBindVertexArray(vao_handle);
    // We draw triangles in the current binded GL_ARRAY_BUFFER and GL_ELEMENT_ARRAY_BUFFER
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // We unbind the attributes
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }


  glfwTerminate();
  return 0;
}
