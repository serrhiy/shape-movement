#version 330 core

in vec3 fargmentColor;

out vec4 fragColor;

void main() {
    fragColor = vec4(fargmentColor, 1.0f);
}
