// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cmath>

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

  GLint num_attributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &num_attributes);
  printf("MAX ATTRIBS NUM: %d\n", num_attributes);

#define HANDLE_COUNT 2
  // We generate a Vertex Buffer Object (VBO)
  GLuint vbo_handles[HANDLE_COUNT];
  glGenBuffers(HANDLE_COUNT, vbo_handles);   // Generate 1 buffer

  // We create our vertex array objects
  GLuint vao_handles[HANDLE_COUNT];
  glCreateVertexArrays(HANDLE_COUNT, vao_handles);

	// We create an Element Buffer Object
  GLuint ebo_handles[HANDLE_COUNT];
  glGenBuffers(HANDLE_COUNT, ebo_handles);

  // We store the information we need to interpret the points
  glBindVertexArray(vao_handles[0]);  // This VAO is now active
  {
    // We send over the vertices
		GLfloat vertices[] = {

      // Positions        // Colors
			 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Top Right
		   0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom Right
	    -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // Top Left
		};
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handles[0]);  // This VBO is active for GL_ARRAY_BUFFER
    // We sent this information to the current binded GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // We set out vertex attrib pointer (how to interpret GL_ARRAY_BUFFER)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // We send over the vertex indices
		GLuint indices[] = {    // Note that we start from 0!
				0, 1, 2,            // First Triangle
		};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_handles[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  }
  // We undind the buffer array
  glBindVertexArray(0);

  glBindVertexArray(vao_handles[1]);
  {
    // We send over the vertices
		GLfloat vertices[] = {
				-0.5f,  0.5f, 0.0f,   // Top Left
				 0.5f, -0.5f, 0.0f,  // Bottom Right
				-0.5f, -0.5f, 0.0f,  // Bottom Left
		};
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handles[1]);  // This VBO is active for GL_ARRAY_BUFFER
    // We sent this information to the current binded GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // We set out vertex attrib pointer (how to interpret GL_ARRAY_BUFFER)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // We send over the vertex indices
		GLuint indices[] = {    // Note that we start from 0!
				0, 1, 2             // Second Triangle
		};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_handles[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  }
  glBindVertexArray(0);


  // DEBUG
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */

  // We create the shader that we're going to use
  std::unique_ptr<Shader> shader_ptr = Shader::CreateFromPaths("shaders/simple.vert",
                                                               "shaders/simple.frag");
  std::unique_ptr<Shader> shader_ptr2 = Shader::CreateFromPaths("shaders/simple.vert",
                                                               "shaders/simple2.frag");

  // We see about the uniform color variable
  std::string pos_offset("vertexOffset");
  GLint offset_handle = glGetUniformLocation(shader_ptr->GetProgramHandle(),
                                             pos_offset.c_str());
  if (offset_handle == -1) {
    printf("COULD NOT FIND VARIABLE FOR: %s\n", pos_offset.c_str());
  }
  std::string color_variable("ourColor");
  GLint color_uniform_handle = glGetUniformLocation(shader_ptr2->GetProgramHandle(),
                                                    color_variable.c_str());
  if (color_uniform_handle == -1) {
    printf("COULD NOT FIND VARIABLE FOR: %s\n", color_variable.c_str());
  }

  // "Game" loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat time_value = glfwGetTime();

    shader_ptr->UseShader();
    // We bind the attributes for this draw call
    // We draw triangles in the current binded GL_ARRAY_BUFFER and GL_ELEMENT_ARRAY_BUFFER
    // We unbind the attributes
    GLfloat offset = (sin(time_value) / 2);
    glUniform3f(offset_handle, offset, 0.0f, offset);

    glBindVertexArray(vao_handles[0]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    shader_ptr2->UseShader();

    // We update the variable
    GLfloat color = (sin(time_value) / 2) + 0.5f;
    glUniform4f(color_uniform_handle, 0.0f, color, 0.0f, 1.0f);

    glBindVertexArray(vao_handles[1]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }


  glfwTerminate();
  return 0;
}
