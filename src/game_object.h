#ifndef _GALAXIAN_GAME_OBJECT_H_
#define _GALAXIAN_GAME_OBJECT_H_
#include <cstdio>
class GameObject {
  public:
    virtual void printInfo() = 0;
  protected:
    GLfloat posx, posy;
  private:
};
#endif
