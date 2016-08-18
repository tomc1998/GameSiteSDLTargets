#include <iostream>
#include <stdlib.h>
#include "renderer.hpp"
#include "input_handler.hpp"
#include "state.hpp"
#include "player.hpp"
#include "target.hpp"
#include "ray.hpp"
#include "texture_manager.hpp"
//#include <ft2build.h>
//#include FT_FREETYPE_H

void initState(State& state) {
  state.player = new Player(0, 0, 90);
  state.SCREEN_WIDTH = 800;
  state.SCREEN_HEIGHT = 600;
  state.endflag = 0;
  state.targets.push_back(new Target(1, 0, 0, 1));
}

int main() {
  State state;
  initState(state);
  initRenderer(state);

  while (!state.endflag) {
    handleInput(state);
    state.update();
    render(state);
  }

  destroyRenderer(state);
  return 0;
}
