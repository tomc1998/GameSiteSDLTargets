#ifndef STATE_HPP
#define STATE_HPP
#include <SDL/SDL.h>
#include <vector>

class Target;
class Player;
class Ray;

class State {
public:
  State();
  void update();

  SDL_Window* window;
  SDL_GLContext glContext;
  int endflag;
  int SCREEN_WIDTH, SCREEN_HEIGHT;
  Player* player;
  std::vector<Target*> targets;
  std::vector<Ray*> rays;
};

#endif
