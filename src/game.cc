#include "game.h"
#include "shader.h"
#include "stars.h"
#include "triangle.h"
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
static void key_callback(GLFWwindow*, int, int, int, int);
GLFWwindow *Game::getWindow() {
  return this->window;
}
/// Initialize the glfw and glew libraries
/// 
/// Exits on any error during initialization
void Game::init(int width, int height) {
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
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  Triangle t;
  Stars s(100);
  // Cursor starts at the center // not working
  glfwSetCursorPos(window, 800/2, 600/2);
  while (!glfwWindowShouldClose(window)) {
    // Check for events
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    t.draw();
    s.draw();
    glfwSwapBuffers(window);
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, NULL);
    if (xpos > 800)
      glfwSetCursorPos(window, 800, 300);
    if (xpos < 0)
      glfwSetCursorPos(window, 0, 300);
    double dx = (xpos - 400)/400;
    double max_vel = 0.05f;
    t.move(max_vel*dx);
  }
  glfwTerminate();
}
static void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    // Esc closes the game
    glfwSetWindowShouldClose(window, GL_TRUE);
}
