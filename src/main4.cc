#include "shader.h"
#include "math/matrix.h"
#include "game.h"
#include <iostream>
#include <cstdio>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#define GLEW_STATIC 1
static void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int main() {
  Game g;
  g.init(800, 600);
  GLFWwindow* window = g.getWindow();
  // Vertex shader
  Shader s;
  //TODO how to always get the correct path no matter where the binary file is
  s.compileFromPath("../src/shader.vertexshader",
      "../src/shader.fragmentshader");
  //Set up vertex data (and buffer(s)) and attribute pointers
  GLfloat vertices[] = {
    -0.25f, 0.0f, 0.0f, // Left  
    0.25f, 0.0f, 0.0f, // Right 
    0.0f,  0.5f, 0.0f  // Top   
  };
  glm::mat4 trans;
  trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  //glm::mat4 result = trans * glm::mat4(-0.25f, 0.0f, 0.0f, 1.0f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.05f, 1.0f);
  //printf("%f, %f, %f\n", result.x, result.y, result.z);

  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // Bind the Vertex Array Object first, then bind and set vertex buffer(s)
  //and attribute pointer(s).
  glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
        (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

  //GLint uniTrans = glGetUniformLocation(s.getID(), "trans");
  std::cout << "GLM MATIRX:\n" << glm::to_string(trans) << "\n";
  GLint uniTrans = glGetUniformLocation(s.getID(), "trans");
  //glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[0][0]);

  //Note that this is allowed, the call to glVertexAttribPointer registered
  //VBO as the currently bound vertex buffer object so afterwards we can
  //safely unbind
  glBindVertexArray(0);
  //Unbind VAO (it's always a good thing to unbind any buffer/array to
  //prevent strange bugs)
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glUseProgram(s.getID());
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[0][0]);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(s.getID());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glUniformMatrix4fv(uniTrans, 1, GL_FALSE, &trans[0][0]);
    //printf("Updating\n");
    // Check if any events have been activated (key pressed, mouse moved etc.)
    // and call corresponding response functions
    glfwPollEvents();
    // Render
    // Clear the colorbuffer
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(s.getID());
    //glBindVertexArray(VAO);
      //glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    // Swap the screen buffers
    glfwSwapBuffers(window);
  }
  //Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  //Terminate GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();
  return 0;
}
// Is called whenever a key is pressed/released via GLFW
static void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
