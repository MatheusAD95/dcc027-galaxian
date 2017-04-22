#include "game.h"
#define GLEW_STATIC 1
int main() {
  Game g;
  g.init(500, 700);
  g.start();
  return 0;
}
