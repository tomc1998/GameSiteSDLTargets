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
}

int main() {
  State state;
  initState(state);
  initRenderer(state);
  initSounds();
  SDL_Init(SDL_INIT_TIMER);

  unsigned int currTime = SDL_GetTicks();
  unsigned int prevTime = currTime; 
  float delta = 0;
  while (!state.endflag) {
    prevTime = currTime;
    currTime = SDL_GetTicks();
    delta = (float)(currTime - prevTime)/1000.f;
    handleInput(state, delta);
    state.update(delta);
    render(state);
    if (!state.atTitleScreen) {
      unsigned int ticksElapsed = SDL_GetTicks() - state.tickStart;
      state.spawner.millisBetweenTargets = 1200 - (ticksElapsed)/120;
      state.spawner.targetFadeSpeed = 1 + (float)ticksElapsed/50000.f;
    }
  }

  destroyRenderer(state);
  return 0;
}
