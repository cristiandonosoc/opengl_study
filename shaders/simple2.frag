#version 330

out vec4 color;

uniform vec4 ourColor;

void main() {
  color = vec4(0.0f, 0.5f, 0.2f, 1.0f);
  color = ourColor;
}
