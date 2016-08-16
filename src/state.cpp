#include "state.hpp"
#include "player.hpp"

State::State() {
  player = 0;
}

void State::update() {
  player->update(this);

  for (unsigned ii = 0; ii < targets.size(); ++ii) {
    player->update(this);
  }
}
