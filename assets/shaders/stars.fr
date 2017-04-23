#version 330 core
out vec4 color;
uniform float value;
void main() {
  color = vec4(value*1.0f, value*1.0f, value*1.0, 1.0f);
}
