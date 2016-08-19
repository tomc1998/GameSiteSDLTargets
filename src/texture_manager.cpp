#ifdef WIN32
#include <windows.h>
#endif
#include "texture_manager.hpp"
#include <GL/gl.h>
#include <SDL/SDL_image.h>


GLuint loadTex(const char* filename, GLuint FILTER) {
  SDL_Surface* surf = IMG_Load(filename);

  SDL_PixelFormat pixelFormat;
  pixelFormat.format = SDL_PIXELFORMAT_RGBA8888;
  pixelFormat.palette = NULL;
  pixelFormat.BitsPerPixel = 32;
  pixelFormat.BytesPerPixel = 4;

  pixelFormat.Amask = 0xFF000000;
  pixelFormat.Bmask = 0x00FF0000;
  pixelFormat.Gmask = 0x0000FF00;
  pixelFormat.Rmask = 0x000000FF;

  SDL_Surface* glSurf = SDL_ConvertSurface(surf, &pixelFormat, 0);

  GLuint texID;
  glGenTextures(1, &texID);
  glBindTexture(GL_TEXTURE_2D, texID);

  // Assume mode = RGBA
  int mode = GL_RGBA;

  glTexImage2D(GL_TEXTURE_2D,
               0,
               mode,
               glSurf->w,
               glSurf->h,
               0,
               mode,
               GL_UNSIGNED_BYTE,
               glSurf->pixels);

  SDL_FreeSurface(surf);
  SDL_FreeSurface(glSurf);


  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FILTER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FILTER);
  glBindTexture(GL_TEXTURE_2D, 0);
  return texID;
}

