#ifndef _GALAXIAN_BULLET_H_
#define _GALAXIAN_BULLET_H_
#include <GL/glew.h>
#include "shader.h"
#include "collision/polygon.h"
class Bullet {
  public:
    Bullet(GLfloat dx, GLfloat posx);
    ~Bullet();
    void draw();
    void destroy();
    bool isDestroyed();
    Polygon *getShape();
  private:
    bool destroyed;
    GLfloat dx, dy;
    GLfloat posx, posy;
    Polygon *shape;
    Shader shader;
    GLuint vao, vbo, ebo;
};
#endif
