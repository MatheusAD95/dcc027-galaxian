#ifndef _GALAXIAN_STARS_H_
#define _GALAXIAN_STARS_H_
#include "shader.h"
#include <GL/glew.h>
#include <glfw3.h>
class Stars {
  public:
    Stars(int);
    ~Stars();
    void draw();
  private:
    int n;
    GLuint *vao, *vbo, *ebo;
    Shader shader;
};
#endif
