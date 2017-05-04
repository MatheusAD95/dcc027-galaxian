#ifndef _GALAXIAN_POWERUP
#define _GALAXIAN_POWERUP
#include "collision/polygon.h"
#include "shader.h"
#include "texture.h"
#include "triangle.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
class Powerup {
  public:
    Powerup(GLfloat posx, GLfloat posy);
    void draw();
    bool isColliding(Triangle *t);
  private:
    Shader shader;
    Polygon *shape;
    GLuint vao, vbo, ebo;
    GLfloat posx, posy;
    glm::mat4 trans;
    Texture texture;
};
#endif
