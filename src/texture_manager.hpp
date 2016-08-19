#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

GLuint loadTex(const char* filename, GLuint FILTER);

#endif

