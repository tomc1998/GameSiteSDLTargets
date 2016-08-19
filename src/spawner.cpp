#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include "spawner.hpp"
#include "state.hpp"
#include "target.hpp"
#include "time.h"

Spawner::Spawner() {
  millisBetweenTargets = 1000;
  prevMillis = 0;
  targetCounter = 0;
  targetFadeSpeed = 1;
  srand(time(NULL));
  running = 0;
}

void Spawner::start() {
  running = 1;
  prevMillis = SDL_GetTicks();
}

void Spawner::stop() {
  running = 0;
}

void Spawner::update(State* state, float delta) {
  int currMillis = SDL_GetTicks();
  if (!running) {
    return;
  }
  targetCounter += currMillis - prevMillis;
  prevMillis = currMillis;
  if (targetCounter >= millisBetweenTargets) {
    targetCounter -= millisBetweenTargets;
    float x = ((float)rand() / (float)RAND_MAX)*state->roomWidth*1.5f - state->roomWidth*0.75f;
    float y = ((float)rand() / (float)RAND_MAX)*state->roomHeight*1.5f - state->roomHeight*0.75f;
    float z = ((float)rand() / (float)RAND_MAX)*50 - 3;
    Target* t = new Target(x, y, z, 0);
    t->fadeSpeed = targetFadeSpeed;
    state->targets.push_back(t);
  }
}
