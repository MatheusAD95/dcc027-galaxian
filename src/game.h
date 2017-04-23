#include "triangle.h"
#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
class Game {
  public:
    Game() {};
    void init(int w, int h);
    void start();
  private:
    GLFWwindow *window;
    int width, height;
    void loop();
};
