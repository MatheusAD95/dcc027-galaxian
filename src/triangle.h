#ifndef _GALAXIAN_TRIANGLE_H_
#define _GALAXIAN_TRIANGLE_H_
#include "bullet.h"
#include "game_object.h"
#include "shader.h"
#include "texture.h"
#include "collision/polygon.h"
#include <GL/glew.h>
class Triangle : public GameObject {
  public:
    Triangle();
    ~Triangle();
    void draw();
    void move(GLfloat dx);
    void shoot();
    GLfloat getPosX();
    Bullet *getBullet();
    Polygon *getShape();
    GLuint getHealth();
    void decreaseHealth();
    void increaseHealth();
    void increaseSpeed();
    void decreaseSpeed();
    void printInfo();
  private:
    GLfloat velocity_multiplier;
    GLuint health;
    GLuint vao, vbo;
    GLfloat posx, dx;
    Polygon *shape;
    //GLfloat dx;
    Shader shader;
    Texture *tx[3];
    Bullet *bullet;
};
#endif
