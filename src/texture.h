#ifndef _GALAXIAN_TEXTURE_H_
#define _GALAXIAN_TEXTURE_H_
#include <GL/glew.h>
/// Classe para abstrair o conceito de texturas 2D
class Texture {
  public:
    Texture(const char *);
    ~Texture();
    void bind();
  private:
    GLuint texture;
};
#endif
