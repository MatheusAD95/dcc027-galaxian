#include "texture.h"
#include "SOIL.h"
Texture::Texture(const char *path) {
  int w, h;
  unsigned char* i = SOIL_load_image(path, &w, &h, 0, SOIL_LOAD_RGB);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, i);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(i);
  glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::bind() {
  glBindTexture(GL_TEXTURE_2D, texture);
}
Texture::~Texture() {
  glDeleteTextures(1, &texture);
}
