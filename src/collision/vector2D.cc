#include "vector2D.h"
#include <iostream>
Vector2D::Vector2D(GLfloat x, GLfloat y) {
  this->x = x;
  this->y = y;
}
Vector2D::Vector2D() {
  this->x = 0.0f;
  this->y = 0.0f;
}
void Vector2D::printPoint() {
  std::cout << "(" << x << ", " << y << ")";
}
