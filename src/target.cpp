#include "target.hpp"
#include "vector.hpp"
#include "state.hpp"

void Target::update(State* state) {
}

Target::Target() {
}

Target::Target(float _x, float _y, float _z) {
  pos.x = _x;
  pos.y = _y;
  pos.z = _z;
}

