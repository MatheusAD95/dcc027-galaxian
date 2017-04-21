#include "shader.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
void Shader::compile(const GLchar *vertexShaderSource,
    const GLchar *fragmentShaderSource,
    const GLchar *geometrySource) {
  //Vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderCompileErrors(vertexShader);
  //Fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  checkShaderCompileErrors(fragmentShader);
  //Link shaders
  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertexShader);
  glAttachShader(this->ID, fragmentShader);
  glLinkProgram(this->ID);
  checkProgramCompileErrors(this->ID);
  //Delete shaders since they are already linked
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
GLuint &Shader::getID() {
  return this->ID;
}
void Shader::checkShaderCompileErrors(GLuint shader) {
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cerr << "ERROR: Shader compilation failed\n";
    std::cerr << infoLog << '\n';
    exit(-1); //should we exit??
  }
}
void Shader::checkProgramCompileErrors(GLuint program) {
  GLint success;
  GLchar infoLog[512];
  glGetProgramiv(program, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cerr << "ERROR: Shader linking failed\n";
    std::cerr << infoLog << '\n';
    exit(-1); //should we exit??
  }
}
void Shader::compileFromPath(const GLchar *vertexPath,
    const GLchar *fragmentPath) {
  std::string vertexSource = "";
  std::ifstream vertexSourceFile(vertexPath, std::ios::in);
  if (vertexSourceFile.is_open()) {
    std::string line;
    while (getline(vertexSourceFile, line))
      vertexSource += "\n" + line;
    vertexSourceFile.close();
  }
  std::string fragmentSource = "";
  std::ifstream fragmentSourceFile(fragmentPath, std::ios::in);
  if (fragmentSourceFile.is_open()) {
    std::string line = "";
    while (getline(fragmentSourceFile, line))
      fragmentSource += "\n" + line;
    fragmentSourceFile.close();
  }
  this->compile(vertexSource.c_str(), fragmentSource.c_str());
}
