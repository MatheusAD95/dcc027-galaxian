#include "bullet.h"
#include "game.h"
#include "shader.h"
#include "stars.h"
#include "triangle.h"
#include "alien.h"
#include <cstdlib>
#include <iostream>
static void key_callback(GLFWwindow*, int, int, int, int);
static bool space_pressed = false;
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
  loop();
}
/// Game loop
/// 
/// 
void Game::loop() {
  //glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  Triangle t;
  //Alien t;
  Stars s(100);
  // Cursor starts at the center // not working
  glfwSetCursorPos(window, width/2, height/2);
  while (!glfwWindowShouldClose(window)) {
    // Check for events
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    s.draw();
    t.draw();
    glfwSwapBuffers(window);
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (xpos > width) glfwSetCursorPos(window, width, ypos);
    if (xpos < 0) glfwSetCursorPos(window, 0, ypos);
    // Steps of 15 to velocity instead of being continuous
    int idx = xpos - width/2; idx -= (idx%15);
    double dx = ((double)idx)/(width/2),
           max_vel = 0.05f;
    t.move(max_vel*dx);
    if (space_pressed)
      t.shoot(),
      space_pressed = false;
  }
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
}
