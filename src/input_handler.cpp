#ifdef WIN32
#include <windows.h>
#endif
#include <SDL/SDL.h>
#include "player.hpp"
#include "input_handler.hpp"
#include "state.hpp"
#include "ray.hpp"
#include "collision.hpp"
#include "target.hpp"
#include "sound_manager.hpp"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_timer.h>
#include <iostream>
#include <math.h>
#include <vector>

int W_DOWN = 0;
int A_DOWN = 0;
int S_DOWN = 0;
int D_DOWN = 0;
int Q_DOWN = 0;
int E_DOWN = 0;

float xSens = 1.3f, ySens = 1.3f;

// Callback to SDL_SetTimer
static Uint32 startSpawning(Uint32 interval, void* param) {
  State* state = (State*) param;
  state->atTitleScreen = 0;
  state->tickStart = SDL_GetTicks();
  state->spawner.start();
  return 0;
}

void handleInput(State& state, float delta) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_MOUSEMOTION) {
      state.player->rotX += delta*e.motion.xrel*xSens;
      state.player->rotY += delta*e.motion.yrel*ySens;
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
      if (state.atTitleScreen) {
        Mix_RewindMusic();
        Mix_PlayMusic(soundtrack, -1);
        state.currScore = 0;
        state.currHealth = 3;
        SDL_AddTimer(2000, startSpawning, &state);
      }

      Player* p = state.player;
      Ray* r = new Ray(p->pos.x, p->pos.y, p->pos.z,
                      sin(M_PI/180.f*p->rotX),
                      sin(M_PI/180.f*p->rotY),
                      -cos(-M_PI/180.f*p->rotX));
      std::vector<Vector3f*> intersections = checkRayToTargets(r, state.targets);
      std::vector<unsigned> targetsToRemove;
      for (unsigned ii = 0; ii < intersections.size(); ++ii) {
        if (intersections[ii] != NULL) {
          Mix_PlayChannel(-1, pop, 0);
          ++ state.currScore;
          if (state.currHiScore < state.currScore) {
            state.currHiScore = state.currScore;
          }
          break;
        }
      }
      for (unsigned ii = 0; ii < intersections.size(); ++ii) {
        Vector3f* v = intersections[ii];
        if (v == NULL) { continue; }
        targetsToRemove.push_back(ii);
        delete v;
      }
      for (unsigned ii = 0; ii < targetsToRemove.size(); ++ii) {
        unsigned index = targetsToRemove[ii];
        delete state.targets[index - ii];
        state.targets.erase(state.targets.begin() + index - ii);
      }

      #ifdef DRAW_RAYS
      state.rays.push_back(r);
      #else
      delete r;
      #endif
    }
  }
}


