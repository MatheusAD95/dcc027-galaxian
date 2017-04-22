#include "triangle.h"
#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
class Game {
  public:
    Game() {};
    void init(int w, int h);
    void start();
    static void key_callback(GLFWwindow* window, int key, int scancode,
        int action, int mode) {
      if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
      if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        t.shoot();
        //std::cout << "SPACE PRESSED\n";
    }
  private:
    static Triangle t;
    GLFWwindow *window;
    int width, height;
    void loop();
};
