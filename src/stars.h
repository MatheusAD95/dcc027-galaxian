#ifndef _GALAXIAN_STARS_H_
#define _GALAXIAN_STARS_H_
#include "shader.h"
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
class Stars {
  public:
    Stars(int);
    ~Stars();
    void draw();
  private:
    int n;
    GLuint *vao, *vbo, *ebo;
    Shader shader;
    glm::mat4 *trans;
    GLfloat *value;
    GLfloat *posy;
    int refresh_rate, refresh_cnt;
    //static const GLfloat velocity = 0.01f;
};
#endif
