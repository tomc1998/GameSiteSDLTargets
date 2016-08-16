#include "target.hpp"
#include "vector.hpp"
#include "state.hpp"
#include "collision.hpp"

Plane* Target::getPlane() {
  return new Plane(pos.x, pos.y, pos.z, nor.x, nor.y, nor.z);
}

void Target::update(State* state) {
}

void Target::init(float _x, float _y, float _z,
                  float _norX, float _norY, float _norZ, float _rad) {
  nor.x = _norX;
  nor.y = _norY;
  nor.z = _norZ;
  pos.x = _x;
  pos.y = _y;
  pos.z = _z;
  rad = _rad;
}

Target::Target() {
  init(0, 0, 0, 0, 0, 1, 1);
}

Target::Target(float _x, float _y, float _z, float _rad) {
  init(_x, _y, _z, 0, 0, 1, _rad);
}

