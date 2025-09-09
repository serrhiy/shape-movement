#version 330 core

layout (location = 0) in vec2 position;

uniform mat3 transform;

void main() {
  vec3 transformed = transform * vec3(position, 1);
  gl_Position = vec4(transformed.xy, 0, 1);
}
