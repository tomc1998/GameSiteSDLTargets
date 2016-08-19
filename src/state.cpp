#include <algorithm>
#include <stdlib.h>
#include "state.hpp"
#include "target.hpp"
#include "player.hpp"
#include "ray.hpp"

bool sortTargFunc(Target* t1, Target* t2) {
  return t1->pos.z < t2->pos.z;
}

State::State() {
  player = 0;
  roomWidth = 24;
  roomHeight = 12;
  currScore = 0;
  currHealth = 3;
}

void State::update() {
  // Update everything we have...
  player->update(this);

  std::sort(targets.begin(), targets.end(), sortTargFunc);
  for (unsigned ii = 0; ii < targets.size(); ++ii) {
    targets[ii]->update(this);
    if (targets[ii]->fadingOut && targets[ii]->rad < 0) {
      delete targets[ii];
      targets.erase(targets.begin() + ii);
      -- ii;
    }
  }

  // Spawn stuff!
  spawner.update(this);
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
