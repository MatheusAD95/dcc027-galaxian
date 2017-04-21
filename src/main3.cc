#include "shader.h"
#include "math/matrix.h"
#include <iostream>
#include <cstdio>
#include <GL/glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLEW_STATIC 1
// Function prototypes
void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
// The MAIN function, from here we start the application and run the game loop
int main() {
  // Init GLFW
  glfwInit();
  // Set all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  // Create a GLFWwindow object that we can use for GLFW's functions
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Galaxian", NULL, NULL);
  glfwMakeContextCurrent(window);
  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);
  // Set this to true so GLEW knows to use a modern approach to retrieving
  //function pointers and extensions
  glewExperimental = GL_TRUE;
  // Initialize GLEW to setup the OpenGL Function pointers
  glewInit();
  // Define the viewport dimensions
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);  
  glViewport(0, 0, width, height);
  // Build and compile our shader program
  // Vertex shader
  Shader s;
  //s.compile(vertexShaderSource, fragmentShaderSource);
  s.compileFromPath("../src/shader.vertexshader",
      "../src/shader.fragmentshader");
  //compile
  // Set up vertex data (and buffer(s)) and attribute pointers
  GLfloat vertices[] = {
    -0.25f, 0.0f, 0.0f, // Left  
    0.25f, 0.0f, 0.0f, // Right 
    0.0f,  0.5f, 0.0f  // Top   
  };


  glm::mat4 trans;
  trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  //glm::vec4 result = trans * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
  //printf("%f, %f, %f\n", result.x, result.y, result.z);
  GLint uniTrans = glGetUniformLocation(s.getID(), "trans");
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // Bind the Vertex Array Object first, then bind and set vertex buffer(s)
  //and attribute pointer(s).

  glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);//GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
        (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

  //Note that this is allowed, the call to glVertexAttribPointer registered
  //VBO as the currently bound vertex buffer object so afterwards we can
  //safely unbind
  glBindVertexArray(0);
  //Unbind VAO (it's always a good thing to unbind any buffer/array to
  //prevent strange bugs)
  // Game loop
  int cnt = 0;
  while (!glfwWindowShouldClose(window)) {

    //vertices[0] += 0.01f;
    //getchar();

    // Check if any events have been activiated (key pressed, mouse moved etc.)
    // and call corresponding response functions
    glfwPollEvents();
    // Render
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //translate(vertices, 0.01, 0.0);
    //getchar();
    // Draw our first triangle
    glUseProgram(s.getID());

    glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
          (GLvoid*)0);
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Swap the screen buffers
    glfwSwapBuffers(window);

    //printf("loop %d\n", ++cnt);
    //getchar();
  }
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  // Terminate GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();
  return 0;
}
// Is called whenever a key is pressed/released via GLFW
void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
