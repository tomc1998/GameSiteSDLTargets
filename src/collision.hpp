#ifndef COLLISION_HPP
#define COLLISION_HPP
#include <vector>
#include "vector.hpp"
class Ray;
class Target;

class Plane {
public:
  Plane();
  Plane(float _x, float _y, float _z,
        float _norX, float _norY, float _norZ);
  Vector3f pos;
  Vector3f nor;
  
private:
  void init(float _x, float _y, float _z,
            float _norX, float _norY, float _norZ);
};

std::vector<Vector3f*> checkRayToPlanes(Ray* r, std::vector<Plane*> planes);
std::vector<Vector3f*> checkRayToTargets(Ray* r, std::vector<Target*> targets);

#endif
