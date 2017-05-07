#ifndef _GALAXIAN_ALIEN_H_
#define _GALAXIAN_ALIEN_H_
#include "bullet.h"
#include "powerup.h"
#include "shader.h"
#include "triangle.h"
#include "texture.h"
#include "collision/polygon.h"
#include "game_object.h"
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
class Alien {// : public GameObject {
  public:
    Alien(int n);
    ~Alien();
    void draw();
    void updateAttackPosition(GLfloat posx);
    Powerup *collision(Bullet *b);
    bool collision(Triangle *t);
  private:
    //GLuint *attacking;
    int n;
    GLuint *vao, *vbo, *ebo, texture;
    Shader shader;
    Polygon **shape;
    bool *dead, *attacking, *returning;
    Bullet **shooting;
    glm::mat4 *trans;
    GLfloat *value;
    int direction;
    GLfloat *posx, *posy,
            *return_posx, *return_posy;
    Texture *t[4];
    unsigned refresh_cnt, refresh_rate, frame, loop_direction;
    GLfloat spaceship_posx;
};
#endif
