#ifndef _GALAXIAN_TRIANGLE_H_
#define _GALAXIAN_TRIANGLE_H_
#include "bullet.h"
#include "game_object.h"
#include "shader.h"
#include "texture.h"
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
  private:
    GLuint vao, vbo;
    GLfloat posx, dx;
    //GLfloat dx;
    Shader shader;
    Texture *tx[3];
    Bullet *bullet;
};
#endif
