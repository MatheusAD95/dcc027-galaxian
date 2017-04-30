#include "triangle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <SOIL.h>
Bullet *Triangle::getBullet() {
  return this->bullet;
}
GLfloat Triangle::getPosX() {
  return this->posx;
}
Triangle::Triangle() {
  posx = 0.0f;
  posy = -0.8f; //0.8 is the top, should we center??
  shader.compileFromPath("../assets/shaders/spaceship.vt",
      "../assets/shaders/spaceship.fr");
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
  GLfloat vertices[] = {
    -0.07f, -0.95f, 0.0f, 0.0f,
    0.07f, -0.95f, 1.0f, 0.0f,
    0.0f,  -0.8f, 0.5f, 1.0f
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat),
      (GLvoid *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT,GL_FALSE, 4*sizeof(GLfloat),
      (GLvoid*)(2*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // Textures
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  tx[0] = new Texture("../assets/spv2.png");
  tx[1] = new Texture("../assets/spv4r.png");
  tx[2] = new Texture("../assets/spv4l.png");
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
  // Use a different texture depending on the direction and velocity
  if (this->dx >= 0.02) tx[1]->bind();
  else if (this->dx <= -0.02) tx[2]->bind();
  else tx[0]->bind();
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
