#ifndef _MATHEUSAD_SHADER_H_
#define _MATHEUSAD_SHADER_H_
#include <GL/glew.h>
#include <string>
class Shader {
  public:
    GLuint ID;
    Shader() {};
    void compile(const GLchar *vertexSource,
        const GLchar *fragmentSource,
        const GLchar *geometrySource = NULL);
    void compileFromPath(const GLchar *vertexSourceCode,
        const GLchar *fragmentSourceCode);
    GLuint &getID();
  private:
    void checkShaderCompileErrors(GLuint object);
    void checkProgramCompileErrors(GLuint object);
};
#endif
