#include <SDL/SDL.h>
#include "player.hpp"
#include "input_handler.hpp"
#include "state.hpp"
#include "ray.hpp"
#include "collision.hpp"
#include <iostream>
#include <math.h>
#include <vector>

int W_DOWN = 0;
int A_DOWN = 0;
int S_DOWN = 0;
int D_DOWN = 0;
int Q_DOWN = 0;
int E_DOWN = 0;

float xSens = 0.02f, ySens = 0.02f;

void handleInput(State& state) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_MOUSEMOTION) {
      state.player->rotX += e.motion.xrel*xSens;
      state.player->rotY += e.motion.yrel*ySens;
    }
    else if (e.type == SDL_KEYDOWN) {
      if (e.key.keysym.sym == SDLK_ESCAPE) {
        state.endflag = 1;
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
      else if (e.key.keysym.sym == SDLK_q) {
        Q_DOWN = 1;
      }
      else if (e.key.keysym.sym == SDLK_e) {
        E_DOWN = 1;
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
      else if (e.key.keysym.sym == SDLK_q) {
        Q_DOWN = 0;
      }
      else if (e.key.keysym.sym == SDLK_e) {
        E_DOWN = 0;
      }
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN) {
      Player* p = state.player;
      Ray* r = new Ray(p->pos.x, p->pos.y, p->pos.z,
                      -sin(-M_PI/180.f*p->rotX),
                      -sin(-M_PI/180.f*p->rotY),
                      -cos(-M_PI/180.f*p->rotX));
      std::vector<Vector3f*> intersections = checkRayToTargets(r, state.targets);
      for (unsigned ii = 0; ii < intersections.size(); ++ii) {
        Vector3f* v = intersections[ii];
        if (v == NULL) { continue; }
        std::cout << "Intersection: " << v->x << ", " << v->y << ", " << v->z << std::endl;
      }
      state.rays.push_back(r);
    }
  }
}

