#ifndef _GALAXIAN_TRIANGLE_H_
#define _GALAXIAN_TRIANGLE_H_
#include "bullet.h"
#include "shader.h"
#include <GL/glew.h>
class Triangle {
  public:
    Triangle();
    ~Triangle();
    void draw();
    void move(GLfloat dx);
    void shoot();
  private:
    GLuint vao, vbo, texture, tx2, tx3;
    GLfloat posx, dx;
    Shader shader;
    Bullet *bullet;
};
#endif
