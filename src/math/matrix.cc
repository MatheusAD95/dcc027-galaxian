#include "matrix.h"
void translate(GLfloat *m, GLfloat dx, GLfloat dy) {
  m[0] += dx;
  m[3] += dx;
  m[6] += dx;
}
