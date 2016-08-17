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
  srand(time(NULL));
}

void Spawner::update(State* state) {
  int currMillis = SDL_GetTicks();
  targetCounter += currMillis - prevMillis;
  prevMillis = currMillis;
  if (targetCounter >= millisBetweenTargets) {
    targetCounter -= millisBetweenTargets;
    float x = ((float)rand() / (float)RAND_MAX)*20 - 10;
    float y = ((float)rand() / (float)RAND_MAX)*7 - 2;
    float z = ((float)rand() / (float)RAND_MAX)*6 - 3;
    Target* t = new Target(x, y, z, 1);
    state->targets.push_back(t);
  }
}
