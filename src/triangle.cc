#include "triangle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <SOIL.h>
Triangle::Triangle() {
  posx = 0.0f;
  // TODO path shouldn't be relative!
  shader.compileFromPath("../src/triangle.vertex", "../src/triangle.frag");
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
  GLfloat vertices[] = {
    -0.07f, -0.95f, 0.0f, 0.0f,
    0.07f, -0.95f, 1.0f, 0.0f,
    0.0f,  -0.8f, 0.5f, 1.0f
  };
  //GLfloat vertices[] = {
  //  -0.05f, -0.99f,
  //  0.05f, -0.99f,
  //  0.0f,  -0.8f,
  //};
  //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat),
      (GLvoid *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT,GL_FALSE, 4*sizeof(GLfloat),
      (GLvoid*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // Textures
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int width, height;
  unsigned char* image = SOIL_load_image("../assets/spv2.png", &width,
      &height, 0, SOIL_LOAD_RGB);
  unsigned char* image2 = SOIL_load_image("../assets/spv32.png", &width,
      &height, 0, SOIL_LOAD_RGB);
  unsigned char* image3 = SOIL_load_image("../assets/spv33.png", &width,
      &height, 0, SOIL_LOAD_RGB);
  printf("w %d h %d\n", width, height);

  glGenTextures(1, &texture);

  glGenTextures(1, &tx2);

  glGenTextures(1, &tx3);

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
      GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);


  glBindTexture(GL_TEXTURE_2D, tx2);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
      GL_UNSIGNED_BYTE, image2);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image2);


  glBindTexture(GL_TEXTURE_2D, tx3);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
      GL_UNSIGNED_BYTE, image3);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image3);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  bullet = NULL;
}
void Triangle::move(GLfloat dx) {
  this->dx = dx;
  posx += dx;
  if (posx >= 0.93f) posx = 0.93f, this->dx = 0;
  if (posx <= -0.93f) posx = -0.93f, this->dx = 0;
}
void Triangle::shoot() {
  if (bullet != NULL)
    return;
  bullet = new Bullet(dx/2, posx);
}
void Triangle::draw() {
  glUseProgram(shader.getID());
  glm::mat4 trans;
  trans = glm::translate(trans, glm::vec3(posx, 0.0f, 0.0f));
  GLint uniTrans = glGetUniformLocation(shader.getID(), "trans");
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[0][0]);
  if (this->dx >= 0.02)
    glBindTexture(GL_TEXTURE_2D, tx2);
  else if (this->dx <= -0.02)
    glBindTexture(GL_TEXTURE_2D, tx3);
  else
    glBindTexture(GL_TEXTURE_2D, texture);
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
  if (bullet != NULL) {
    bullet->draw();
    if (bullet->isDestroyed()) {
      delete bullet;
      bullet = NULL;
    }
  }
}
Triangle::~Triangle() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}
