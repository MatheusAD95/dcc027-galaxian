#include "bullet.h"
#include <cstdio>
#include <glm/gtc/matrix_transform.hpp>
Polygon *Bullet::getShape() {
  return this->shape;
}
static GLfloat width = 0.004f,
               height = 0.03f;
static const GLfloat VELOCITY = 0.015f;
Bullet::Bullet(GLfloat dx, GLfloat posx, GLfloat posy, GLint dir) {
  Vector2D points[4];
  points[0].x = posx + width, points[0].y = posy - height;
  points[1].x = posx - width, points[1].y = posy - height;
  points[2].x = posx - width, points[2].y = posy + height;
  points[3].x = posx + width, points[3].y = posy + height;
  shape = new Polygon(4, points);
  this->destroyed = false;
  this->dx = dx;
  this->dy = dir*VELOCITY;
  this->posy = posy;
  this->posx = posx;
  shader.compileFromPath("../assets/shaders/bullet.vt",
      "../assets/shaders/bullet.fr");
  srand(time(NULL));
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
  double x1 = width, x2 = -width,
         y1 = -height, y2 = height;
  GLfloat vert[] = {
    x1, y1,
    x2, y1,
    x2, y2,
    x1, y2
  };
  glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vert), vert, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
  };
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
      GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat),
      (GLvoid *)0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
bool Bullet::isDestroyed() {
  return destroyed;
}
void Bullet::destroy() {
  this->destroyed = true;
}
void Bullet::draw() {
  posx += dx; // TODO before or after translate? which is better?
  posy += dy;
  Vector2D points[4];
  points[0].x = posx + width, points[0].y = posy - height;
  points[1].x = posx - width, points[1].y = posy - height;
  points[2].x = posx - width, points[2].y = posy + height;
  points[3].x = posx + width, points[3].y = posy + height;
  delete shape;
  shape = new Polygon(4, points);

  glUseProgram(shader.getID());
  glm::mat4 trans;
  if (posy >= 1 || posy <= -1.3) {
    destroyed = true;
    return;
  }
  trans = glm::translate(trans, glm::vec3(posx, posy, 0.0f));
  GLint uniTrans = glGetUniformLocation(shader.getID(), "trans");
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[0][0]);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}
Bullet::~Bullet() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
  delete shape;
}
