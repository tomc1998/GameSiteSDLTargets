#ifndef TARGET_HPP
#define TARGET_HPP
#include "vector.hpp"
#include "collision.hpp"

class State;
class Target {
public:
  Target();
  Target(float _x, float _y, float _z, float rad);
  void update(State* state);
  Plane* getPlane(); // Gets the plane that the target lies on
  Vector3f pos;
  Vector3f nor;
  Vector3f vel;
  Vector3f acc;
  float rad;
  float maxRad;
  int fadingOut;
  float fadeSpeed;
private:
  void init(float _x, float _y, float _z,
            float _norX, float _norY, float _norZ, float _rad);
};

#endif
