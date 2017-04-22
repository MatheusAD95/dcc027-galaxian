#include <GL/glew.h>
#include <glfw3.h>
class Game {
  public:
    Game() {};
    void init(int w, int h);
    GLFWwindow *getWindow();
    void start();
  private:
    GLFWwindow *window;
    int width, height;
    void loop();
};
