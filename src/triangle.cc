#include "triangle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
Triangle::Triangle() {
  posx = 0.0f;
  // TODO path shouldn't be relative!
  shader.compileFromPath("../src/shader.vertex", "../src/shader2.frag");
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
  GLfloat vertices[] = {
    -0.05f, -0.99f,
    0.05f, -0.99f,
    0.0f,  -0.8f
  };
  //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat),
      (GLvoid *)0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Triangle::move(GLfloat dx) {
  posx += dx;
  if (posx >= 0.95f) posx = 0.95f;
  if (posx <= -0.95f) posx = -0.95f;
}
void Triangle::draw() {
  glUseProgram(shader.getID());
  glm::mat4 trans;
  trans = glm::translate(trans, glm::vec3(posx, 0.0f, 0.0f));
  GLint uniTrans = glGetUniformLocation(shader.getID(), "trans");
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[0][0]);
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}
Triangle::~Triangle() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}
