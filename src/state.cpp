#include <stdlib.h>
#include "state.hpp"
#include "target.hpp"
#include "player.hpp"
#include "ray.hpp"

State::State() {
  player = 0;
}

void State::update() {
  player->update(this);

  for (unsigned ii = 0; ii < targets.size(); ++ii) {
    player->update(this);
  }
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
