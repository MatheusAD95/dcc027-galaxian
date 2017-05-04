#include "bullet.h"
#include "game.h"
#include "powerup.h"
#include "shader.h"
#include "stars.h"
#include "triangle.h"
#include "alien.h"
#include <cstdlib>
#include <iostream>
#include <vector>
//TODO check if debug mode is working correctly
static void key_callback(GLFWwindow*, int, int, int, int);
static void
mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static bool space_pressed = false,
            right_mouse_btn = false,
            debug_mode = false,
            step = false,
            restart = false;
/// Initialize the glfw and glew libraries
/// 
/// Exits on any error during initialization
void Game::init(int width, int height) {
  this->width = width;
  this->height = height;
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    exit(-1);
  }
  // Hint GLFW version 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Hint OpenGL version
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // No resizing
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  this->window = glfwCreateWindow(width, height, "Galaxian", NULL, NULL);
  if (!this->window) {
    std::cerr << "Failed to open GLFW window.";
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(this->window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  // Mouse input configuration
  glfwSetInputMode(window, GLFW_CURSOR, 0);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW\n";
    glfwTerminate();
    exit(-1);
  }
}
/// 
/// 
/// 
void Game::start() {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);  
  // Define the viewport dimensions
  glViewport(0, 0, width, height);
  // Create objects here?
  // Go into main loop
  restart = false;
  loop();
}
/// Game loop
/// 
/// 
void Game::loop() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  Triangle *t = new Triangle();
  Alien *a = new Alien(30);
  Stars *s = new Stars(500);
  std::vector <Powerup *> powerups;
  Powerup *p;
  // Cursor starts at the center // not working
  glfwSetCursorPos(window, width/2, height/2);
  bool paused = false;
  while (!glfwWindowShouldClose(window)) {
    // Check for events
    glfwPollEvents();
    if (restart) {
      delete a;
      delete t;
      delete s;
      t = new Triangle();
      a = new Alien(30);
      s = new Stars(500);
      restart = false;
    }
    if (step)
      step = false, right_mouse_btn = true;
    else if (right_mouse_btn)
      continue;
    glClear(GL_COLOR_BUFFER_BIT);
    s->draw();
    t->draw();
    a->draw();
    a->updateAttackPosition(t->getPosX());
    Powerup *pup;
    if ((pup = a->collision(t->getBullet()))) {
      t->getBullet()->destroy();
      powerups.push_back(pup);
    }
    for (int i = 0, e = powerups.size(); i < e; ++i) {
      Powerup *p = powerups[i];
      p->draw();
      if (p->isColliding(t)) {
        powerups.erase(powerups.begin() + i);
        delete p;
      }
    }
    if (a->collision(t))
      t->decreaseHealth();
    //std::cout << a.collision(t.getBullet()) << "\n";
    glfwSwapBuffers(window);
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (xpos > width) glfwSetCursorPos(window, width, ypos);
    if (xpos < 0) glfwSetCursorPos(window, 0, ypos);
    // Steps of 15 to velocity instead of being continuous
    int idx = xpos - width/2; idx -= (idx%15);
    double dx = ((double)idx)/(width/2),
           max_vel = 0.05f;
    t->move(max_vel*dx);
    if (space_pressed)
      t->shoot(),
      space_pressed = false;
    if (!t->getHealth()) {
      std::cout << "GAME OVER\n";
      break;
    }
  }
  delete a;
  delete t;
  delete s;
  glfwTerminate();
}
static void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  // Esc closes the game
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  // Space shoots
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    space_pressed = true;
  if (key == GLFW_KEY_D && action == GLFW_PRESS)
    step = true;
  if (key == GLFW_KEY_R && action == GLFW_PRESS)
    restart = true;
}
static void
mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    right_mouse_btn = !right_mouse_btn;
}
