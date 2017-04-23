#include "alien.h"
#include <SOIL.h>
#include <iostream>
#include  <cstdlib>
#include <ctime>
#include <cstdlib>
static double dRand() {
  int sign = rand()%2 ? 1 : -1;
  return ((double)rand()/RAND_MAX)*sign;
}
static double radius = 0.05f;
Alien::Alien(int n) {
  refresh_cnt = frame = 0;
  refresh_rate = 10;
  loop_direction = 1;
  this->direction = 1;
  this->n = n;
  shader.compileFromPath("../assets/shaders/alien.vt",
      "../assets/shaders/alien.fr");
  srand(time(NULL));
  vao = (GLuint *)malloc(n*sizeof(GLuint));
  vbo = (GLuint *)malloc(n*sizeof(GLuint));
  ebo = (GLuint *)malloc(n*sizeof(GLuint));
  posx = (GLfloat *)malloc(n*sizeof(GLfloat));
  glGenBuffers(n, vbo);
  glGenVertexArrays(n, vao);
  glGenBuffers(n, ebo);
  for (int i = 0; i < n; ++i) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
    glBindVertexArray(vao[i]);
    double x1 = -radius, x2 = radius,
           y1 = -radius, y2 = radius;
    GLfloat vert[] = {
      x1, y1, 0.0f, 0.0f,
      x2, y1, 1.0f, 0.0f,
      x2, y2, 1.0f, 1.0f,
      x1, y2, 0.0f, 1.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
    GLuint elements[] = {
      0, 1, 2,
      2, 3, 0
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
        GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat),
        (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT,GL_FALSE, 4*sizeof(GLfloat),
        (GLvoid*)(2*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }
  trans = (glm::mat4 *)malloc(n*sizeof(glm::mat4));
  glm::mat4 initial;
  double margin_left = -0.70f,
         margin_right = 0.70f;
  double y = 0.8f;
  int new_row = 0;
  for (int i = 0; i < n; ++i) {
    double x = margin_left + 0.15f*(i - new_row);
    if (x >= margin_right)
      y -= 0.12f, new_row += i, x = margin_left + 0.15f*(i - new_row);
    posx[i] = x;
    trans[i] = glm::translate(initial, glm::vec3(x, y, 0.0f));
  }
  value = (GLfloat *)malloc(n*sizeof(GLfloat));
  t[0] = new Texture("../assets/alien1.png");
  t[1] = new Texture("../assets/alien2.png");
  t[2] = new Texture("../assets/alien3.png");
  t[3] = new Texture("../assets/alien4.png");
}
///
///
///
void Alien::draw() {
  double vel = 0.004f;
  glUseProgram(shader.getID());
  for (int i = 0; i < this->n; ++i) {
    posx[i] += vel*direction;
    trans[i] = glm::translate(trans[i],
        glm::vec3(vel*direction, 0.00f, 0.0f));
    GLint uniTrans = glGetUniformLocation(shader.getID(), "trans");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[i][0][0]);
    glBindVertexArray(vao[i]);
    t[frame]->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
  for (int i = 0; i < n; ++i) 
    if (posx[i] >= 0.9f || posx[i] <= -0.9f) {
      direction *= -1;
      break;
    }
  ++refresh_cnt;
  if (refresh_cnt == refresh_rate) {
    if (frame  == 0)
      loop_direction = 1;
    if (frame == 3)
      loop_direction = -1;
    refresh_cnt = 0;
    frame = (frame + loop_direction);
  }
}
///
///
///
Alien::~Alien() {
  glDeleteVertexArrays(n, vao);
  glDeleteBuffers(n, vbo);
  glDeleteBuffers(n, ebo);
  delete t[0];
  delete t[1];
  delete t[2];
  delete t[3];
  free(posx);
  free(vao);
  free(vbo);
  free(trans);
}
