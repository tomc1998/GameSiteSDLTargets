#include <iostream>
#include <stdlib.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <math.h>
#include "renderer.hpp"
#include "player.hpp"
#include "state.hpp"
#include "ray.hpp"
#include "target.hpp"
#include "texture_manager.hpp"

static GLuint texCrosshair = 0;
static GLuint texShadowCentre = 0;
static GLuint texTarget = 0;
static GLuint texHP = 0;
static GLuint fontTex = -1;
static TTF_Font* scoreFont = 0;
static SDL_Color scoreColor = {150, 150, 150};

void drawHealth(unsigned numHP) {
  glBegin(GL_QUADS);
  glColor4f(1, 0, 0, 1);
  for (unsigned ii = 0; ii < numHP; ++ii) {
    glTexCoord2f(0, 0); glVertex3f(-1.73f + ii * 0.2f, 0.8f, -2);
    glTexCoord2f(1, 0); glVertex3f(-1.73f + ii * 0.2f + 0.15f, 0.8f, -2);
    glTexCoord2f(1, 1); glVertex3f(-1.73f + ii * 0.2f + 0.15f, 0.8f + 0.15f, -2);
    glTexCoord2f(0, 1); glVertex3f(-1.73f + ii * 0.2f, 0.8f + 0.15f, -2);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
}

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
  glTexCoord2f(0, 0); glVertex3f(x - rad, y - rad, z);
  glTexCoord2f(1, 0); glVertex3f(x + rad, y - rad, z);
  glTexCoord2f(1, 1); glVertex3f(x + rad, y + rad, z);
  glTexCoord2f(0, 1); glVertex3f(x - rad, y + rad, z);
}

void initRenderer(State& state) {

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); 

  state.window = SDL_CreateWindow("SDL OpenGL Test",
                            0, 0,
                            state.SCREEN_WIDTH, state.SCREEN_HEIGHT,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

  // Capture cursor
  SDL_SetRelativeMouseMode(SDL_TRUE);

  // Create context
  state.glContext = SDL_GL_CreateContext(state.window);

  // Set up projection matrices
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspectRatio = (float) state.SCREEN_WIDTH / (float) state.SCREEN_HEIGHT;
  glFrustum(-aspectRatio, aspectRatio, 1, -1, 2, 500);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glClearColor(0,0,0,1);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  IMG_Init(IMG_INIT_PNG);
  texCrosshair    = loadTex("res/crosshair.png",     GL_NEAREST);
  texShadowCentre = loadTex("res/shadow_centre.png", GL_LINEAR);
  texTarget       = loadTex("res/target.png",        GL_LINEAR);
  texHP           = loadTex("res/hp.png",            GL_NEAREST);

  TTF_Init();
  scoreFont = TTF_OpenFont("res/SourceSansPro-Black.otf", 512);
  glGenTextures(1, &fontTex);
}

void drawWalls(State& state) {
  glBindTexture(GL_TEXTURE_2D, texShadowCentre);
  glBegin(GL_QUADS);
  // floor
  glTexCoord2f(0, 0);
  glVertex3f(-state.roomWidth,  state.roomHeight, -7);
  glTexCoord2f(1, 0);
  glVertex3f( state.roomWidth,  state.roomHeight, -7);
  glTexCoord2f(1, 1);
  glVertex3f( state.roomWidth,  state.roomHeight,  100);
  glTexCoord2f(0, 1);
  glVertex3f(-state.roomWidth,  state.roomHeight,  100);

  // roof
  glTexCoord2f(0, 0);
  glVertex3f(-state.roomWidth, -state.roomHeight, -7);
  glTexCoord2f(1, 0);
  glVertex3f( state.roomWidth, -state.roomHeight, -7);
  glTexCoord2f(1, 1);
  glVertex3f( state.roomWidth, -state.roomHeight,  100);
  glTexCoord2f(0, 1);
  glVertex3f(-state.roomWidth, -state.roomHeight,  100);

  // left
  glTexCoord2f(0, 0);
  glVertex3f(-state.roomWidth, -state.roomHeight, -7);
  glTexCoord2f(1, 0);
  glVertex3f(-state.roomWidth,  state.roomHeight, -7);
  glTexCoord2f(1, 1);
  glVertex3f(-state.roomWidth,  state.roomHeight,  100);
  glTexCoord2f(0, 1);
  glVertex3f(-state.roomWidth, -state.roomHeight,  100);

  // right
  glTexCoord2f(0, 0);
  glVertex3f( state.roomWidth, -state.roomHeight, -7);
  glTexCoord2f(1, 0);
  glVertex3f( state.roomWidth,  state.roomHeight, -7);
  glTexCoord2f(1, 1);
  glVertex3f( state.roomWidth,  state.roomHeight,  100);
  glTexCoord2f(0, 1);
  glVertex3f( state.roomWidth, -state.roomHeight,  100);
  
  // far end
  glTexCoord2f(0, 0);
  glVertex3f(-state.roomWidth, -state.roomHeight, -7);
  glTexCoord2f(1, 0);
  glVertex3f( state.roomWidth, -state.roomHeight, -7);
  glTexCoord2f(1, 1);
  glVertex3f( state.roomWidth,  state.roomHeight, -7);
  glTexCoord2f(0, 1);
  glVertex3f(-state.roomWidth,  state.roomHeight, -7);

  // behind
  glTexCoord2f(0, 0);
  glVertex3f(-state.roomWidth, -state.roomHeight, 100);
  glTexCoord2f(1, 0); 
  glVertex3f( state.roomWidth, -state.roomHeight, 100);
  glTexCoord2f(1, 1);
  glVertex3f( state.roomWidth,  state.roomHeight, 100);
  glTexCoord2f(0, 1);
  glVertex3f(-state.roomWidth,  state.roomHeight, 100);

  //glColor3f(0.4f, 0.2f, 0.2f);
  // Draw barrier
  glTexCoord2f(0, .5f);
  glVertex3f(-state.roomWidth, state.roomHeight-5, 60);
  glTexCoord2f(1, .5f); 
  glVertex3f( state.roomWidth, state.roomHeight-5, 60);
  glTexCoord2f(1, 0);
  glVertex3f( state.roomWidth, state.roomHeight, 60);
  glTexCoord2f(0, 0);
  glVertex3f(-state.roomWidth, state.roomHeight, 60);

  glTexCoord2f(0, .5f);
  glVertex3f(-state.roomWidth, state.roomHeight-5, 60);
  glTexCoord2f(1, .5f); 
  glVertex3f( state.roomWidth, state.roomHeight-5, 60);
  glTexCoord2f(1, 0);
  glVertex3f( state.roomWidth, state.roomHeight-5, 55);
  glTexCoord2f(0, 0);
  glVertex3f(-state.roomWidth, state.roomHeight-5, 55);


  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
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

  // Draw walls
  glColor3f(1, 1, 1);
  drawWalls(state);

  glBindTexture(GL_TEXTURE_2D, texTarget);
  glBegin(GL_QUADS);
  for (unsigned ii = 0; ii < state.targets.size(); ++ii) {
    Target* t = state.targets[ii];
    glColor4f(0.5f + (t->pos.z+3)/80.f, 0, 0, 1);
    drawTarget(t->pos.x, t->pos.y, t->pos.z, t->rad, 100);
  }
  glEnd();

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
  glBindTexture(GL_TEXTURE_2D, texCrosshair);
  glBegin(GL_QUADS);
  glColor4f(1, 1, 1, 0.8f);
  glTexCoord2f(0, 0);
  glVertex3f(-0.02f, -0.02f, -2);
  glTexCoord2f(1, 0);
  glVertex3f( 0.02f, -0.02f, -2);
  glTexCoord2f(1, 1);
  glVertex3f( 0.02f,  0.02f, -2);
  glTexCoord2f(0, 1);
  glVertex3f(-0.02f,  0.02f, -2);

  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);

  glPopMatrix();

  // Render score
  SDL_PixelFormat pixelFormat;
  pixelFormat.format = SDL_PIXELFORMAT_RGBA8888;
  pixelFormat.palette = NULL;
  pixelFormat.BitsPerPixel = 32;
  pixelFormat.BytesPerPixel = 4;

  pixelFormat.Amask = 0xFF000000;
  pixelFormat.Bmask = 0x00FF0000;
  pixelFormat.Gmask = 0x0000FF00;
  pixelFormat.Rmask = 0x000000FF;
  
  char score[20];
  sprintf(score, "%d", state.currScore);
  SDL_Surface* fontSurf = TTF_RenderText_Solid(scoreFont, score, scoreColor);
  SDL_Surface* glFontSurf = SDL_ConvertSurface(fontSurf, &pixelFormat, 0);
  glBindTexture(GL_TEXTURE_2D, fontTex);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               glFontSurf->w,
               glFontSurf->h,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               glFontSurf->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  SDL_FreeSurface(fontSurf);
  SDL_FreeSurface(glFontSurf);

  glBegin(GL_QUADS);
  glColor4f(1, 0.9f, 1, 0.3f);
  glTexCoord2f(0, 0); glVertex3f(-0.4f,  0.2f, -2);
  glTexCoord2f(1, 0); glVertex3f( 0.4f,  0.2f, -2);
  glTexCoord2f(1, 1); glVertex3f( 0.4f,  1.0f, -2);
  glTexCoord2f(0, 1); glVertex3f(-0.4f,  1.0f, -2);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texHP);

  glColor4f(1, 1, 1, 1);
  drawHealth(state.currHealth);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  SDL_GL_SwapWindow(state.window);
}
