#include "powerup.h"
static const
GLfloat WIDTH = 0.02f,
        HEIGHT = 0.02f,
        VELOCITY = -0.02f;
Powerup::Powerup(GLfloat posx, GLfloat posy, const char *texture_path) :
  texture(texture_path) {
  this->posx = posx;
  this->posy = posy;
  shader.compileFromPath("../assets/shaders/powerup.vt",
      "../assets/shaders/powerup.fr");
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
  GLfloat x1 = -WIDTH, x2 = WIDTH,
          y1 = -HEIGHT, y2 = HEIGHT;
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
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
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
  trans = glm::translate(trans, glm::vec3(posx, posy, 0.0f));

  Vector2D points[4];
  points[0].x = posx + WIDTH, points[0].y = posy - HEIGHT;
  points[1].x = posx - WIDTH, points[1].y = posy - HEIGHT;
  points[2].x = posx - WIDTH, points[2].y = posy + HEIGHT;
  points[3].x = posx + WIDTH, points[3].y = posy + HEIGHT;
  shape = new Polygon(4, points);
}
void Powerup::draw() {
  GLfloat dy = VELOCITY;
  posy += dy;
  Vector2D points[4];
  points[0].x = posx + WIDTH, points[0].y = posy - HEIGHT;
  points[1].x = posx - WIDTH, points[1].y = posy - HEIGHT;
  points[2].x = posx - WIDTH, points[2].y = posy + HEIGHT;
  points[3].x = posx + WIDTH, points[3].y = posy + HEIGHT;
  delete shape;
  shape = new Polygon(4, points);
  trans = glm::translate(trans, glm::vec3(0.0f, dy, 0.0f));
  glUseProgram(shader.getID());
  GLint uniTrans = glGetUniformLocation(shader.getID(), "trans");
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[0][0]);
  glBindVertexArray(vao);
  texture.bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
bool Powerup::isColliding(Triangle *t) {
  if (shape->isColliding(t->getShape())) {
    upgradeShip(t);
    return true;
  }
  return false;
}
Powerup::~Powerup() {
  delete shape;
}
