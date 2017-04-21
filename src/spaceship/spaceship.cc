#include "spaceship.h"
Spaceship::Spaceship() {
  vertices[0] = -0.5f;
  vertices[1] = -0.5f;
  vertices[2] = 0.0f;
  vertices[3] = 0.5f;
  vertices[4] = -0.5f;
  vertices[5] = 0.0f;
  vertices[6] = 0.0f;
  vertices[7] = 0.5f;
  vertices[8] = 0.0f;
}
Spaceship::Init() {
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}
