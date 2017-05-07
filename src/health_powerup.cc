#include "health_powerup.h"
HealthPowerup::HealthPowerup(GLfloat posx, GLfloat posy) :
  Powerup(posx, posy, "../assets/increase_health_powerup.png") {
}
void HealthPowerup::upgradeShip(Triangle *t) {
  t->increaseHealth();
}
