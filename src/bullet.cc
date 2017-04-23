#include "bullet.h"
#include <glm/gtc/matrix_transform.hpp>
Bullet::Bullet(GLfloat dx, GLfloat posx) {
  this->destroyed = false;
  this->dx = dx;
  this->dy = 0.045f;
  this->posy = -0.82;
  this->posx = posx;
  shader.compileFromPath("../assets/shaders/bullet.vt",
      "../assets/shaders/bullet.fr");
  srand(time(NULL));
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
  double x1 = 0.004f, x2 = -0.004f,
         y1 = 0.0f, y2 = y1 + 0.01f;
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
void Bullet::draw() {
  glUseProgram(shader.getID());
  glm::mat4 trans;
  posx += dx; // TODO before or after translate? which is better?
  posy += dy;
  if (posy >= 1) {
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
}
