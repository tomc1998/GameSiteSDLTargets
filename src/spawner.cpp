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
  targetFadeSpeed = 0.01f;
  srand(time(NULL));
}

void Spawner::update(State* state) {
  int currMillis = SDL_GetTicks();
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
