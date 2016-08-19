#ifndef STATE_HPP
#define STATE_HPP
#include <SDL/SDL.h>
#include <vector>
#include "vector.hpp"
#include "spawner.hpp"

class Target;
class Player;
class Ray;

class State {
public:
  State();
  ~State();
  void update();

  // SUPER Hacky, but positions of the area you can move in
  float backPos, frontPos, leftPos, rightPos;
  
  float roomWidth, roomHeight;
  SDL_Window* window;
  SDL_GLContext glContext;
  int endflag;
  int SCREEN_WIDTH, SCREEN_HEIGHT;
  Player* player;
  std::vector<Target*> targets;
  std::vector<int> targetsAlive;
  std::vector<Ray*> rays;
  int currScore;
  unsigned currHealth;

  Spawner spawner; // Spawns targets

  
};

#endif
