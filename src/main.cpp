#include <SDL/SDL.h>
#include <iostream>
#include <stdlib.h>
#include "renderer.hpp"
#include "input_handler.hpp"
#include "state.hpp"
#include "player.hpp"
#include "target.hpp"
#include "ray.hpp"

void initState(State& state) {
  state.player = new Player(0, 0, 15);
  state.SCREEN_WIDTH = 800;
  state.SCREEN_HEIGHT = 600;
  state.endflag = 0;
  state.targets.push_back(new Target(0, 0, 10));
}

int main() {
  State state;
  initState(state);
  initRenderer(state);

  while (!state.endflag) {
    handleInput(state);
    state.update();
    render(state);
    SDL_GL_SwapWindow(state.window);
  }
 
  destroyRenderer(state);
  return 0;
}
