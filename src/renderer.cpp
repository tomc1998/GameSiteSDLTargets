#include <iostream>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <math.h>
#include "renderer.hpp"
#include "player.hpp"
#include "state.hpp"
#include "ray.hpp"
#include "target.hpp"

void drawRay(Ray* ray) {
  if (ray->hit) {
    glColor4f(1, 1, 0, 1);
  }
  else {
    glColor4f(0, 1, 1, 1);
  }
  glVertex3f(ray->origin.x, ray->origin.y, ray->origin.z);
  glVertex3f(ray->origin.x + ray->direction.x*10000.f,
             ray->origin.y + ray->direction.y*10000.f,
             ray->origin.z + ray->direction.z*10000.f);
}

void drawTarget(float x, float y, float z, float rad, unsigned iter) {
  glColor4f(1, 0, 0, 1);
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(x, y, z);
  glColor4f(0.8f, 0, 0, 1);
  for (unsigned ii; ii <= iter; ++ii) {
    float angle = 2.f*M_PI*(float)ii/(float)iter;
    glVertex3f(x + rad*cos(angle), y + rad*sin(angle), z);
  }
  glEnd();
}

void initRenderer(State& state) {
  state.window = SDL_CreateWindow("SDL OpenGL Test",
                            0, 0,
                            state.SCREEN_WIDTH, state.SCREEN_HEIGHT,
                            SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

  // Capture cursor
  SDL_SetRelativeMouseMode(SDL_TRUE);

  // Create context
  state.glContext = SDL_GL_CreateContext(state.window);

  // Set up projection matrices
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspectRatio = (float) state.SCREEN_WIDTH / (float) state.SCREEN_HEIGHT;
  glFrustum(-aspectRatio, aspectRatio, 1, -1, 2, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glClearColor(0,0,0,1);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void destroyRenderer(State& state) {
  SDL_DestroyWindow(state.window);
  SDL_GL_DeleteContext(state.glContext);
}

//#define DRAW_RAYS
void render(State& state) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, state.SCREEN_WIDTH, state.SCREEN_HEIGHT);

  glPushMatrix();
  glLoadIdentity();
  glRotatef(-state.player->rotY, 1, 0, 0);
  glRotatef(state.player->rotX, 0, 1, 0);
  glTranslatef(-state.player->pos.x, -state.player->pos.y, -state.player->pos.z);

  for (unsigned ii = 0; ii < state.targets.size(); ++ii) {
    Target* t = state.targets[ii];
    glColor4f(0, 1, 0, 1);
    drawTarget(t->pos.x, t->pos.y, t->pos.z, t->rad, 100);
  }

  #ifdef DRAW_RAYS
  glBegin(GL_LINES);
  for (unsigned ii = 0; ii < state.rays.size(); ++ii) {
    Ray* r = state.rays[ii];
    drawRay(r);
  }
  glEnd();
  #endif

  glPopMatrix();
  
  // GUI
  glPushMatrix();
  glLoadIdentity();

  // Crosshair
  glBegin(GL_LINES);
  glColor3f(0, 1, 0);
  glVertex3f(-0.075f, 0, -5);
  glVertex3f(-0.04f, 0, -5);
  glVertex3f(0.07f, 0, -5);
  glVertex3f(0.03f, 0, -5);
  glVertex3f(0, -0.075f, -5);
  glVertex3f(0, -0.04f, -5);
  glVertex3f(0, 0.07f, -5);
  glVertex3f(0, 0.03f, -5);
  glEnd();

  glPopMatrix();
}
