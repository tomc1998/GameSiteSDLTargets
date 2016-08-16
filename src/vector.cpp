#include "vector.hpp"

Vector3f::Vector3f() {
  x = 0;
  y = 0;
  z = 0;
}

Vector3f::Vector3f(float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
}

float Vector3f::dot(const Vector3f& vec) {
  return x*vec.x + y*vec.y + z*vec.z;
}

Vector3f Vector3f::add(const Vector3f& vec) const {
  return Vector3f(x + vec.x, y + vec.y, z + vec.z);
}

Vector3f Vector3f::sub(const Vector3f& vec) const {
  return Vector3f(x - vec.x, y - vec.y, z - vec.z);
}

Vector3f Vector3f::cross(const Vector3f& vec) const {
  return Vector3f(y*vec.z - z*vec.y,
                  z*vec.x - x*vec.z,
                  x*vec.y - y*vec.x);
}

int Vector3f::isZero() const {
  return x == 0 && y == 0 && z == 0;
}


