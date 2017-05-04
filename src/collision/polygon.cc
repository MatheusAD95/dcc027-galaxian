#include "polygon.h"
#include <cstdlib>
#include <iostream>
Polygon::Polygon(GLuint n, Vector2D *p) {
  this->n = n;
  points = (Vector2D *)malloc(n*sizeof(Vector2D));
  for (GLuint i = 0; i < n; ++i)
    points[i].x = p[i].x, points[i].y = p[i].y;
}
Polygon::~Polygon() {
  free(points);
}
static GLfloat Or2(Vector2D A, Vector2D B, Vector2D C) {
  return  (A.x*B.y - A.y*B.x) - (A.x*C.y - A.y*C.x) + (B.x*C.y - B.y*C.x);
}
static bool properIntersect(Vector2D P, Vector2D Q, Vector2D R, Vector2D S) {
  return (Or2(P, Q, R) * Or2(P, Q, S) < 0) &&
    (Or2(R, S, P) * Or2(R, S, Q) < 0);
}
bool Polygon::isColliding(Polygon *p) {
  Vector2D *p_points = p->points;
  GLuint p_n = p->n;
  //std::cout << "BEGIN:\n";
  for (int i = 0; i < n; ++i) {
    int ii = (i + 1)%n;
    for (int j = 0; j < p_n; ++j) {
      int jj = (j + 1)%p_n;
      Vector2D  p1 = points[i],
                p2 = points[ii],
                p3 = p_points[j],
                p4 = p_points[jj];
      //p1.printPoint();
      //std::cout << " ";
      //p2.printPoint();
      //std::cout << " ";
      //p3.printPoint();
      //std::cout << " ";
      //p4.printPoint();
      if (properIntersect(points[i], points[ii], p_points[j], p_points[jj]))
        //std::cout << "(this one)\n";
        return true;
      //std::cout << "\n";
    }
  }
  //std::cout << "END\n\n";
  return false;
}
