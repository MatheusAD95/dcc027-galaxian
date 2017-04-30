#ifndef _GALAXIAN_VECTOR2D_H_
#define _GALAXIAN_VECTOR2D_H_
#include "GL/glew.h"
class Vector2D {
  public:
    Vector2D();
    Vector2D(GLfloat x, GLfloat y);
    void printPoint();
    GLfloat x, y;
};
#endif
