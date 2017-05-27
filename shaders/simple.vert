#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 vertexColor;
out vec3 vertexPosition;

uniform vec3 vertexOffset;

void main() {
  vec3 finalPos = vertexOffset + vec3(pos.x, pos.y, pos.z);
  gl_Position = vec4(finalPos, 1.0f);
  vertexPosition = pos;
  vertexColor = color;
}
