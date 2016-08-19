#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif
#include <algorithm>
#include <SDL/SDL_mixer.h>
#include <stdlib.h>
#include "renderer.hpp"
#include "input_handler.hpp"
#include "state.hpp"
#include "player.hpp"
#include "target.hpp"
#include "ray.hpp"
#include "texture_manager.hpp"
#include "sound_manager.hpp"
#undef main
//#include <ft2build.h>
//#include FT_FREETYPE_H

void initState(State& state) {
  state.player = new Player(0, 0, 90);
  state.SCREEN_WIDTH = 1366;
  state.SCREEN_HEIGHT = 768;
  state.endflag = 0;
  state.targets.push_back(new Target(1, 0, 0, 1));
}

int main() {
  State state;
  initState(state);
  initRenderer(state);
  initSounds();

  while (!state.endflag) {
    handleInput(state);
    state.update();
    render(state);
    state.spawner.millisBetweenTargets = 1200 - std::min(1000, ((int)SDL_GetTicks())/100);
  }

  destroyRenderer(state);
  return 0;
}
