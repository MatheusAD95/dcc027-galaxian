#include "bullet.h"
#include <glm/gtc/matrix_transform.hpp>
Bullet::Bullet() {
  shader.compileFromPath("../src/shader.vertex", "../src/stars.frag");
  srand(time(NULL));
  vao = (GLuint *)malloc(n*sizeof(GLuint));
  vbo = (GLuint *)malloc(n*sizeof(GLuint));
  ebo = (GLuint *)malloc(n*sizeof(GLuint));
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
  glBindVertexArray(vao[i]);
  double x1 = 0.0f, x2 = x1 + 0.008f,
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
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
      GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat),
      (GLvoid *)0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Bullet::draw() {
  glUseProgram(shader.getID());
  glm::mat4 trans;
  trans = glm::translate(trans, glm::vec3(dx, dy, 0.0f));
  //std::cout << "GLM MATIRX:\n" << glm::to_string(trans) << "\n";
  GLint uniTrans = glGetUniformLocation(shader.getID(), "trans");
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[0][0]);
  GLint uniValue = glGetUniformLocation(shader.getID(), "value");
  GLfloat value = dRand();
  glUniform1f(uniValue, value);
  glBindVertexArray(vao[i]);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}
Bullet::~Bullet() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
}
