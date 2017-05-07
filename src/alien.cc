#include "alien.h"
#include "powerup.h"
#include "health_powerup.h"
#include "movespeed_powerup.h"
#include <SOIL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
static double dRand() {
  int sign = rand()%2 ? 1 : -1;
  return ((double)rand()/RAND_MAX)*sign;
}
static double radius = 0.045f;
Alien::Alien(int n) {
  //attacking = n + 1;
  spaceship_posx = 0.0f;
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
  posy = (GLfloat *)malloc(n*sizeof(GLfloat));
  return_posx = (GLfloat *)malloc(n*sizeof(GLfloat));
  return_posy = (GLfloat *)malloc(n*sizeof(GLfloat));
  shape = (Polygon **)malloc(n*sizeof(Polygon *));
  dead = (bool *)calloc(n, sizeof(bool));
  attacking = (bool *)calloc(n, sizeof(bool));
  returning = (bool *)calloc(n, sizeof(bool));
  shooting = (Bullet **)calloc(n, sizeof(Bullet *));
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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat),
        (GLvoid *)(2*sizeof(GLfloat)));
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
      y -= 0.12f, new_row = i, x = margin_left + 0.15f*(i - new_row);
    posx[i] = x;
    posy[i] = y;
    trans[i] = glm::translate(initial, glm::vec3(x, y, 0.0f));
    double x1 = -radius, x2 = radius,
           y1 = -radius, y2 = radius;
    Vector2D points[4];
    points[0].x = posx[i] + x1, points[0].y = posy[i] + y1;
    points[1].x = posx[i] + x2, points[1].y = posy[i] + y1;
    points[2].x = posx[i] + x2, points[2].y = posy[i] + y2;
    points[3].x = posx[i] + x1, points[3].y = posy[i] + y2;
    shape[i] = new Polygon(4, points);
  }
  value = (GLfloat *)malloc(n*sizeof(GLfloat));
  t[0] = new Texture("../assets/alien1.png");
  t[1] = new Texture("../assets/alien2.png");
  t[2] = new Texture("../assets/alien3.png");
  t[3] = new Texture("../assets/alien4.png");
}
Powerup *Alien::collision(Bullet *b) {
  if (b == NULL) return NULL;
  for (int i = 0; i < n; ++i) {
    if (dead[i]) continue;
    if (shape[i]->isColliding(b->getShape())) {
      b->destroy();
      dead[i] = true;
      Powerup *p = NULL;
      GLuint r = rand()%300;
      if (r < 150)
        p = new HealthPowerup(posx[i], posy[i]);
      else if (r < 300)
        p = new MovespeedPowerup(posx[i], posy[i]);
      return p;
    }
  }
  return NULL;
}
bool Alien::collision(Triangle *t) {
  for (int i = 0; i < n; ++i) {
    if (dead[i]) continue;
    if (shape[i]->isColliding(t->getShape())) {
      dead[i] = true;
      return true;
    }
    Bullet *b = shooting[i];
    if (b && t->getShape()->isColliding(b->getShape())) {
      b->destroy();
      return true;
    }
  }
  return false;
}
void Alien::updateAttackPosition(GLfloat posx) {
  spaceship_posx = posx;
  GLuint attack = rand()%300;
  if (attack == 1) {
    GLuint attacker = rand()%n;
    int cnt = 100;
    while (--cnt && (attacking[attacker] || dead[attacker]))
      attacker = rand()%n;
    if (!cnt) return;
    attacking[attacker] = true;
    return_posx[attacker] = this->posx[attacker];
    return_posy[attacker] = this->posy[attacker];
  }
  //
}
///
///
///
void Alien::draw() {
  double x1 = -radius, x2 = radius,
         y1 = -radius, y2 = radius;
  double vel = 0.004f;
  glUseProgram(shader.getID());
  for (int i = 0; i < this->n; ++i) {
    if (dead[i])
      continue;
    GLfloat dx = vel*direction,
            dy = 0.0f;
    return_posx[i] += dx;
    if (attacking[i]) {
      dy = -1.5*vel;
      GLfloat dist = spaceship_posx - posx[i];
      if (dist <= 0.04f && dist >= -0.04f) dx = 0.0f;
      else if (spaceship_posx > posx[i]) dx = 1.5*vel;
      else dx = -1.5*vel;
      GLfloat tgt = Bullet::aim(dx, posx[i], posy[i], spaceship_posx);
      if (!shooting[i] && tgt < 0.1f && tgt >= -0.1f)
        shooting[i] = new Bullet(dx, posx[i], posy[i], -1);
    } else if (returning[i]) {
      // dx value
      GLfloat distx = return_posx[i] - posx[i];
      if (distx <= 0.02f && distx >= -0.02f) dx = distx;
      else if (return_posx[i] > posx[i]) dx = 2*vel;
      else dx = -2*vel;
      // dy value
      GLfloat disty = return_posy[i] - posy[i];
      if (disty <= 0.02f && disty >= -0.02f) dy = disty;
      else if (return_posy[i] < posy[i]) dy = -vel;
      //continue normal movement after it reaches its position
      if (posx[i] == return_posx[i] && posy[i] == posy[i])
        returning[i] = false;
    }
    posy[i] += dy;
    posx[i] += dx;
    // when the alien reaches the bottom of the screen, it returns to the top
    if (posy[i] <= -1.0f) {
      returning[i] = true, attacking[i] = false;
      posy[i] = 1.1f;
      glm::mat4 initial;
      trans[i] = glm::translate(initial,
          glm::vec3(posx[i], posy[i], 0.0f));
    }
    Vector2D points[4];
    points[0].x = posx[i] + x1, points[0].y = posy[i] + y1;
    points[1].x = posx[i] + x2, points[1].y = posy[i] + y1;
    points[2].x = posx[i] + x2, points[2].y = posy[i] + y2;
    points[3].x = posx[i] + x1, points[3].y = posy[i] + y2;
    delete shape[i];
    shape[i] = new Polygon(4, points);

    trans[i] = glm::translate(trans[i],
        glm::vec3(dx, dy, 0.0f));
    GLint uniTrans = glGetUniformLocation(shader.getID(), "trans");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[i][0][0]);
    glBindVertexArray(vao[i]);
    t[frame]->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
  for (int i = 0; i < n; ++i) {
    if (dead[i])
      continue;
    if (posx[i] >= 0.9f || posx[i] <= -0.9f) {
      direction *= -1;
      break;
    }
    if (attacking[i] && (return_posx[i] >= 0.9f || return_posx[i] <= -0.9f)) {
      direction *= -1;
      break;
    }
  }
  for (int i = 0; i < n; ++i) {
    Bullet *b = shooting[i];
    if (!b) continue;
    if (b->isDestroyed())
      delete b, shooting[i] = NULL;
    else
      b->draw();
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
  for (int i = 0; i < n; ++i)
    delete shape[i];
  free(shape);
  free(dead);
  free(attacking);
  free(returning);
  free(shooting);
  glDeleteVertexArrays(n, vao);
  glDeleteBuffers(n, vbo);
  glDeleteBuffers(n, ebo);
  delete t[0];
  delete t[1];
  delete t[2];
  delete t[3];
  free(posx);
  free(posy);
  free(vao);
  free(vbo);
  free(trans);
}
