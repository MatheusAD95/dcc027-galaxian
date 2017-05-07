#include "movespeed_powerup.h"
MovespeedPowerup::MovespeedPowerup(GLfloat posx, GLfloat posy) :
  Powerup(posx, posy, "../assets/increase_movespeed_powerup.png") {
}
void MovespeedPowerup::upgradeShip(Triangle *t) {
  t->increaseSpeed();
}
