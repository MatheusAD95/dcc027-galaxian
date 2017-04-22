#ifndef _GALAXIAN_BULLET_H_
#define _GALAXIAN_BULLET_H_
class Bullet {
  public:
    Bullet();
    ~Bullet();
  private:
    Shader shader;
    GLuint vao, vbo, ebo;
};
#endif
