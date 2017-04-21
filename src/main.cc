#include "game.h"
#define GLEW_STATIC 1
int main() {
  Game g;
  g.init(800, 600);
  g.start();
  return 0;
}
