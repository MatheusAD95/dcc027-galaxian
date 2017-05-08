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
Polygon *Triangle::getShape() {
  return this->shape;
}
GLuint Triangle::getHealth() {
  return this->health;
}

void Triangle::decreaseHealth() {
  --this->health;
}
void Triangle::increaseHealth() {
  ++this->health;
  if (health > 3) health = 3;
}
void Triangle::increaseSpeed() {
  this->velocity_multiplier *= 1.33f;
}
void Triangle::decreaseSpeed() {
  this->velocity_multiplier /= 1.33f;
}
Triangle::Triangle() {
  // starting health
  this->health = 2;
  velocity_multiplier = 1.0f;
  //GLfloat x1 = -0.07f, x2 = -x1,
  posx = 0.0f;
  //posy = -0.8f; //0.8 is the top, should we center??
  posy = 0.0f;

  Vector2D points[3];
  points[0].x = posx - 0.07f, points[0].y = posy - 0.95f;
  points[1].x = posx + 0.07f, points[1].y = posy - 0.95f;
  points[2].x = posx + 0.00f, points[2].y = posy - 0.80f;
  shape = new Polygon(3, points);

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
  this->dx = velocity_multiplier*dx;
  //std::cout << "dx: " << this->dx;
  posx += this->dx;
  Vector2D points[3];
  points[0].x = posx - 0.07f, points[0].y = posy - 0.95f;
  points[1].x = posx + 0.07f, points[1].y = posy - 0.95f;
  points[2].x = posx + 0.00f, points[2].y = posy - 0.80f;
  delete shape;
  shape = new Polygon(3, points);
  if (posx >= 0.93f) posx = 0.93f, this->dx = 0;
  if (posx <= -0.93f) posx = -0.93f, this->dx = 0;
}
void Triangle::shoot() {
  if (bullet != NULL)
    return;
  bullet = new Bullet(dx/2, posx);
}
#include <iostream>
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

  //heath bar
  glm::mat4 trans2;
  for (int i = 0; i < this->health; ++i) {
    trans = glm::scale(trans2, glm::vec3(0.3f, 0.3f, 1.0f));
    trans = glm::translate(trans, glm::vec3(-3.2f + 0.15f*i, -2.30f, 0.0f));
    uniTrans = glGetUniformLocation(shader.getID(), "trans");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  glBindVertexArray(0);


  if (bullet != NULL) {
    bullet->draw();
    if (bullet->isDestroyed()) {
      delete bullet;
      bullet = NULL;
    }
  }

  //glBindVertexArray(vao);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
  //glBindVertexArray(0);

}
Triangle::~Triangle() {
  if (bullet)
    delete bullet;
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}
void Triangle::printInfo() {
  printf("Spaceship={pos=(%.2lf,%.2lf), vel=%.2lf, health=%d, shooting=%d};\n",
      this->posx, -0.82, this->dx, this->health, (this->bullet != NULL));
  if (this->bullet != NULL)
    bullet->printInfo();
  printf("\n");
}
