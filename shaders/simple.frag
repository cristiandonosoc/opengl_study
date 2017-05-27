#version 330

in vec3 vertexColor;
in vec3 vertexPosition;

out vec4 color;

void main() {
  /* color = vec4(1.0f, 0.5f, 0.2f, 1.0f); */
  color = vec4(vertexPosition.xyz, 1.0f);
}
