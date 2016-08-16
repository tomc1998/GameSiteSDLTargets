#include "ray.hpp"

Ray::Ray() {
}

Ray::Ray(float _x, float _y, float _z,
         float _xdir, float _ydir, float _zdir) {
  origin.x = _x;
  origin.y = _y;
  origin.z = _z;
  direction.x = _xdir;
  direction.y = _ydir;
  direction.z = _zdir;
}


