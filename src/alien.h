#ifndef _GALAXIAN_ALIEN_H_
#define _GALAXIAN_ALIEN_H_
#include "shader.h"
#include "texture.h"
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
class Alien {
  public:
    Alien(int n);
    ~Alien();
    void draw();
  private:
    int n;
    GLuint *vao, *vbo, *ebo, texture;
    Shader shader;
    glm::mat4 *trans;
    GLfloat *value;
    int direction;
    GLfloat *posx;
    Texture *t[4];
    unsigned refresh_cnt, refresh_rate, frame, loop_direction;
};
#endif
