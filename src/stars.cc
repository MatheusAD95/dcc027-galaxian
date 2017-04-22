#include "stars.h"
#include <ctime>
#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>
static double dRand() {
  int sign = rand()%2 ? 1 : -1;
  return ((double)rand()/RAND_MAX)*sign;
}
Stars::Stars(int n) {
  this->n = n;
  shader.compileFromPath("../src/shader.vertex", "../src/stars.frag");
  srand(time(NULL));
  vao = (GLuint *)malloc(n*sizeof(GLuint));
  vbo = (GLuint *)malloc(n*sizeof(GLuint));
  ebo = (GLuint *)malloc(n*sizeof(GLuint));
  glGenBuffers(n, vbo);
  glGenVertexArrays(n, vao);
  glGenBuffers(n, ebo);
  for (int i = 0; i < n; ++i) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
    glBindVertexArray(vao[i]);
    double x1 = 0.0f, x2 = x1 + 0.008f,
           y1 = 0.0f, y2 = y1 + 0.01f;
    //printf("(%lf %lf), (%lf %lf)\n", x1, x2, y1, y2);
    GLfloat vert[] = {
      x1, y1,
      x2, y1,
      x2, y2,
      x1, y2
    };
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vert, GL_STATIC_DRAW);

    //vert[0] = x1, vert[1] = y1;
    //vert[2] = x2, vert[3] = y1;
    //vert[4] = x2, vert[5] = y2;
    //vert[6] = x1, vert[7] = y2;
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
  }
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Stars::draw() {
  glUseProgram(shader.getID());
  for (int i = 0; i < this->n; ++i) {
    glm::mat4 trans;
    double dx = dRand(),
           dy = dRand();
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
}
Stars::~Stars() {
  glDeleteVertexArrays(n, vao);
  glDeleteBuffers(n, vbo);
  glDeleteBuffers(n, ebo);
  free(vao);
  free(vbo);
}
