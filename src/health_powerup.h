#ifndef _GALAXIAN_HEALTH_POWERUP
#define _GALAXIAN_HEALTH_POWERUP
#include "powerup.h"
class HealthPowerup : public Powerup {
  public:
    HealthPowerup(GLfloat posx, GLfloat posy);
    void upgradeShip(Triangle *t);
  private:
};
#endif
