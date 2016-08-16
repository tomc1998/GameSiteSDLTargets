#ifndef TARGET_HPP
#define TARGET_HPP
#include "vector.hpp"

class State;
class Target {
public:
  Target();
  Target(float _x, float _y, float _z);
  void update(State* state);
  Vector3f pos;
  Vector3f vel;
  Vector3f acc;
};

#endif
