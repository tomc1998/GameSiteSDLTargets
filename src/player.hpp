#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "vector.hpp"

class State;
class Player {
public:
  Player();
  Player(float _x, float _y, float _z);
  void update(State* state);
  Vector3f pos;
  Vector3f vel;
  Vector3f acc;
  float rotX, rotY;
  float rad;
private:
  void init(float _x, float _y, float _z);
};

#endif
