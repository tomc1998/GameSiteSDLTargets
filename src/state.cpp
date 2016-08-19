#include <algorithm>
#include <stdlib.h>
#include "state.hpp"
#include "target.hpp"
#include "player.hpp"
#include "ray.hpp"
#include <SDL/SDL_mixer.h>
#include "sound_manager.hpp"


bool sortTargFunc(Target* t1, Target* t2) {
  return t1->pos.z < t2->pos.z;
}

State::State() {
  player = 0;
  roomWidth = 24;
  roomHeight = 12;
  currScore = 0;
  currHealth = 3;

  backPos = 100;
  leftPos = -roomWidth;
  rightPos = roomWidth;
  frontPos = 60;
  atTitleScreen = 1;

  tickStart = 0;
}

void restart(State* state) {
  state->atTitleScreen = 1;
  //Mix_PauseMusic();
  Mix_RewindMusic();
  state->targets.clear();
  std::vector<Target*>().swap(state->targets);   // clear x reallocating 
  state->spawner.stop();
}

void State::update(float delta) {
  // Update everything we have...
  player->update(this, delta);

  std::sort(targets.begin(), targets.end(), sortTargFunc);
  for (unsigned ii = 0; ii < targets.size(); ++ii) {
    if (currHealth == 0) {
      break;
    }
    targets[ii]->update(this, delta);
    if (targets[ii]->fadingOut && targets[ii]->rad < 0) {
      delete targets[ii];
      targets.erase(targets.begin() + ii);
      -- ii;
      -- currHealth;
      if (currHealth == 0) {
        restart(this);
        break;
      }
    }
  }

  // Spawn stuff!
  spawner.update(this, delta);
}

State::~State() {
  unsigned targetsLen = targets.size();
  for (unsigned ii = 0; ii < targetsLen; ++ii) {
    if (targets[ii] != NULL) {
      delete targets[ii];
      targets[ii] = NULL;
    }
  }
  unsigned raysLen = rays.size();
  for (unsigned ii = 0; ii < raysLen; ++ii) {
    if (rays[ii] != NULL) {
      delete rays[ii];
      rays[ii] = NULL;
    }
  }
  delete player;
}
