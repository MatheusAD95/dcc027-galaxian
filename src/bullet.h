#ifndef _GALAXIAN_BULLET_H_
#define _GALAXIAN_BULLET_H_
#include <GL/glew.h>
#include "shader.h"
#include "collision/polygon.h"
#include "game_object.h"
#include "SFML/Audio.hpp"
#include <cstdlib>
#include <iostream>
class Bullet : public GameObject {
  public:
    static
      GLfloat aim(GLfloat dx, GLfloat posx, GLfloat posy, GLfloat targetx) {
      GLfloat dy = 0.015f; // TODO use static const for velocity
      GLfloat targety = -0.82f; // spaceship location
      GLfloat disty = targety - posy,
              distx = targetx - posx;
      int y_steps = disty/dy;
      return targetx - (y_steps*dx + posx);
    }
    Bullet(GLfloat dx, GLfloat posx, GLfloat posy = -0.82f, GLint dir = 1);
    ~Bullet();
    void draw();
    void destroy();
    bool isDestroyed();
    Polygon *getShape();
    void printInfo();
  private:
    bool destroyed;
    GLfloat dx, dy;
    GLfloat posx, posy;
    Polygon *shape;
    Shader shader;
    GLuint vao, vbo, ebo;
    sf::Sound *sound;
    sf::SoundBuffer *buffer;
};
#endif
