#ifndef RAY_HPP
#define RAY_HPP
#include "vector.hpp"

class Ray {
public:
  Ray();
  Ray(float _x, float _y, float _z,
      float _xdir, float _ydir, float _zdir);

  Vector3f origin;
  Vector3f direction;
};

#endif
