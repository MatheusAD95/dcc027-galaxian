#ifndef _GALAXIAN_BULLET_H_
#define _GALAXIAN_BULLET_H_
#include <GL/glew.h>
#include "shader.h"
class Bullet {
  public:
    Bullet(GLfloat dx, GLfloat posx);
    ~Bullet();
    void draw();
    bool isDestroyed();
  private:
    bool destroyed;
    GLfloat dx, dy;
    GLfloat posx, posy;
    Shader shader;
    GLuint vao, vbo, ebo;
};
#endif
