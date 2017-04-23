#include "stars.h"
#include <ctime>
#include <cstdlib>
/// Generates a random double number
/// Used to translate each star to a different position to create the effect
/// of fast movement
///
static double dRand() {
  int sign = rand()%2 ? 1 : -1;
  return ((double)rand()/RAND_MAX)*sign;
}
Stars::Stars(int n) {
  refresh_rate = 10;
  refresh_cnt = 0;
  this->n = n;
  shader.compileFromPath("../assets/shaders/common.vt",
      "../assets/shaders/stars.fr");
  srand(time(NULL));
  vao = (GLuint *)malloc(n*sizeof(GLuint));
  vbo = (GLuint *)malloc(n*sizeof(GLuint));
  ebo = (GLuint *)malloc(n*sizeof(GLuint));
  glGenBuffers(n, vbo);
  glGenVertexArrays(n, vao);
  glGenBuffers(n, ebo);
  posy = (GLfloat *)malloc(n*sizeof(GLfloat));
  for (int i = 0; i < n; ++i) {
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
  }
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  trans = (glm::mat4 *)malloc(n*sizeof(glm::mat4));
  // set initial position for each star
  glm::mat4 initial;
  for (int i = 0; i < n; ++i) {
    double x = dRand(), y = dRand();
    trans[i] = glm::translate(initial, glm::vec3(x, y, 0.0f));
    posy[i] += y;
  }
  value = (GLfloat *)malloc(n*sizeof(GLfloat));
  // generate a random value bigger than 0.25
  // (if the value is too low, the star is both black and doesn't move)
  for (int i = 0; i < n; ++i)
    value[i] = 0.25 + 3*dRand()/4;

}
///
///
///
#include <iostream>
void Stars::draw() {
  glUseProgram(shader.getID());
  for (int i = 0; i < this->n; ++i) {
    //glm::mat4 initial;
    // if (!refresh_cnt) {
    //   double dx = dRand(),
    //          dy = dRand();
    posy[i] += value[i]*(-0.02f);
    //std::cout << posy[i] << "\n";
    if (posy[i] <= -1.0f) {
      //std::cout << "Star leaving!\n";
      //trans[i] = glm::t
      glm::mat4 initial;
      posy[i] = 1.0f;
      trans[i] = glm::translate(initial, glm::vec3(dRand(), 1.0, 0.0f));
      value[i] = 0.5f + dRand()/2;
      //value[i] = 1.0f;
    } else {
      trans[i] = glm::translate(trans[i],
          glm::vec3(0.0f, value[i]*(-0.02f), 0.0f));
    }
    // }
    GLint uniTrans = glGetUniformLocation(shader.getID(), "trans");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[i][0][0]);
    GLint uniValue = glGetUniformLocation(shader.getID(), "value");
    //GLfloat value = dRand();
    glUniform1f(uniValue, value[i]);
    glBindVertexArray(vao[i]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
  //refresh_cnt = (refresh_cnt + 1)%refresh_rate;
}
///
///
///
Stars::~Stars() {
  glDeleteVertexArrays(n, vao);
  glDeleteBuffers(n, vbo);
  glDeleteBuffers(n, ebo);
  free(posy);
  free(vao);
  free(vbo);
  free(trans);
}
