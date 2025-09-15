#version 330 core

layout (location = 0) in vec4 position;
uniform vec3 color;

out vec3 fargmentColor;

void main() {
  gl_Position = position;
  fargmentColor = color;
}
