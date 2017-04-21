#include "shader.h"
#include <GL/glew.h>
class Triangle {
  public:
    Triangle();
    ~Triangle();
    void draw();
    void move(GLfloat dx);
  private:
    GLuint vao, vbo;
    GLfloat posx;
    Shader shader;
};
