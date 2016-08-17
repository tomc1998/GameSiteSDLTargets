#include "texture_manager.hpp"
#include <GL/gl.h>
#include <SDL/SDL_image.h>


GLuint loadTex(const char* filename) {
  SDL_Surface* surf = IMG_Load(filename);
  GLuint texID;
  glGenTextures(1, &texID);
  glBindTexture(GL_TEXTURE_2D, texID);

  // Assume mode = RGBA
  int mode = GL_RGBA;

  glTexImage2D(GL_TEXTURE_2D,
               0,
               mode,
               surf->w,
               surf->h,
               0,
               mode,
               GL_UNSIGNED_BYTE,
               surf->pixels);


  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  return texID;
}

