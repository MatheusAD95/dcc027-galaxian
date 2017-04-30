#ifndef _GALAXIAN_POLYGON_H_
#define _GALAXIAN_POLYGON_H_
#include "vector2D.h"
class Polygon {
  public:
    Polygon(GLuint n, Vector2D *points);
    ~Polygon();
    bool isColliding(Polygon *p);
  private:
    GLuint n;
    Vector2D *points;
};
#endif
