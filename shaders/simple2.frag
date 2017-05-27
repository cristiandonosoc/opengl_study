#version 330

/* in vec4 vertexColor;  // Same name and type means linking (wow) */

out vec4 color;

uniform vec4 ourColor;

void main() {
  color = vec4(0.0f, 0.5f, 0.2f, 1.0f);
  /* color = vertexColor; */
  color = ourColor;
}
