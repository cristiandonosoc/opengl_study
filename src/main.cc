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

  // We get the shader code
  bool success;
  std::string error_msg;
  Shader test_shader;

  // Vertex shader
  success = test_shader.LoadAndCompileShaderFromFile(Shader::VERTEX,
                                                     "shaders/simple.vert",
                                                     &error_msg);
  if (!success) {
    printf("Error compiling shader: %s\n", error_msg.c_str());
  }

  success = test_shader.LoadAndCompileShaderFromFile(Shader::FRAGMENT,
                                                     "shaders/simple.frag",
                                                     &error_msg);
  if (!success) {
    printf("Error compiling shader: %s\n", error_msg.c_str());
  }




  // "Game" loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    Render();

    glfwSwapBuffers(window);
  }


  glfwTerminate();
  return 0;
}
