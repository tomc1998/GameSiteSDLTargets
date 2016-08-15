#include <SDL/SDL.h>
#include <GL/gl.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

/*
  This is my program! THOOOOMAS CHEEEENG
 */

std::string inventory[28];

SDL_Window* window = NULL;
SDL_GLContext glContext;
int endflag = 0;
int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
float xSens = 0.02f, ySens = 0.02f;
float rotX = 0, rotY = 0;
float xPos = 0, yPos = 0, zPos = 0;

int W_DOWN = 0;
int A_DOWN = 0;
int S_DOWN = 0;
int D_DOWN = 0;

void initSDL() {
  window = SDL_CreateWindow("SDL OpenGL Test",
                            0, 0,
                            SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

  // Create context
  glContext = SDL_GL_CreateContext(window);

  // Set up projection matrices
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspectRatio = (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT;
  glFrustum(-aspectRatio, aspectRatio, 1, -1, 1.5f, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glClearColor(0,0,0,1);

  // Capture cursor
  SDL_SetRelativeMouseMode(SDL_TRUE);
}

void destroySDL() {
  SDL_DestroyWindow(window);
  SDL_GL_DeleteContext(glContext);
}

void handleInput() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_MOUSEMOTION) {
      rotX += e.motion.xrel*xSens;
      rotY += e.motion.yrel*ySens;
    }
    else if (e.type == SDL_KEYDOWN) {
      if (e.key.keysym.sym == SDLK_ESCAPE) {
        endflag = 1;
      }
      else if (e.key.keysym.sym == SDLK_a) {
        A_DOWN = 1;
      }
      else if (e.key.keysym.sym == SDLK_d) {
        D_DOWN = 1;
      }
      else if (e.key.keysym.sym == SDLK_w) {
        W_DOWN = 1;
      }
      else if (e.key.keysym.sym == SDLK_s) {
        S_DOWN = 1;
      }
    }
    else if (e.type == SDL_KEYUP) {
      if (e.key.keysym.sym == SDLK_a) {
        A_DOWN = 0;
      }
      else if (e.key.keysym.sym == SDLK_d) {
        D_DOWN = 0;
      }
      else if (e.key.keysym.sym == SDLK_w) {
        W_DOWN = 0;
      }
      else if (e.key.keysym.sym == SDLK_s) {
        S_DOWN = 0;
      }
    }
  }
}

void handleMovement() {
  if (A_DOWN) {
    xPos += 0.1f*cos(M_PI*rotX/180.f);
    zPos += 0.1f*sin(M_PI*rotX/180.f);
  }
  if (D_DOWN) {
    xPos -= 0.1f*cos(M_PI*rotX/180.f);
    zPos -= 0.1f*sin(M_PI*rotX/180.f);
  }
  if (W_DOWN) {
    xPos -= 0.1f*sin(M_PI*rotX/180.f);
    zPos += 0.1f*cos(M_PI*rotX/180.f);
  }
  if (S_DOWN) {
    xPos += 0.1f*sin(M_PI*rotX/180.f);
    zPos -= 0.1f*cos(M_PI*rotX/180.f);
  }
}

void drawTarget(float x, float y, float z, float rad, unsigned iter) {
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1, 0, 0);
  glVertex3f(x, y, z);
  for (unsigned ii; ii <= iter; ++ii) {
    float angle = 2.f*M_PI*(float)ii/(float)iter;
    glVertex3f(x + rad*cos(angle), y + rad*sin(angle), z);
  }
  glEnd();
}

int main() {

  initSDL();

  while (!endflag) {
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glLoadIdentity();
    glRotatef(-rotY, 1, 0, 0);
    glRotatef(rotX, 0, 1, 0);
    glTranslatef(xPos, yPos, zPos - 15);

    glColor3f(1, 0, 0);
    drawTarget(0, 0, 10, 1, 100);

    SDL_GL_SwapWindow(window);
    handleInput();
    handleMovement();
  }
 
  destroySDL();

  return 0;
}
