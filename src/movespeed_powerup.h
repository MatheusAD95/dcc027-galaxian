#ifndef _GALAXIAN_MS_POWERUP
#define _GALAXIAN_MS_POWERUP
#include "powerup.h"
class MovespeedPowerup : public Powerup {
  public:
    MovespeedPowerup(GLfloat posx, GLfloat posy);
    void upgradeShip(Triangle *t);
  private:
};
#endif
