#include <iostream>
#include "collision.hpp"
#include "ray.hpp"
#include "target.hpp"
#include <stdlib.h>
#include <vector>
#include <math.h>

/* Plane Imp */
void Plane::init(float _x, float _y, float _z,
                 float _norX, float _norY, float _norZ) {
  nor.x = _norX;
  nor.y = _norY;
  nor.z = _norZ;
  pos.x = _x;
  pos.y = _y;
  pos.z = _z;
}

Plane::Plane() {
  init(0, 0, 0, 0, 0, 0);
}

Plane::Plane(float _x, float _y, float _z,
             float _norX, float _norY, float _norZ) {
  init(_x, _y, _z, _norX, _norY, _norZ);
}
/* End Plane Imp */


struct PlaneIntersection {
  Vector3f intersection;
  Plane* plane;
};

/** Returns pointers to intersections - must be freed. Will return
    NULL if there is no intersection. */
std::vector<Vector3f*> checkRayToPlanes(Ray* r, std::vector<Plane*> planes) {
  std::vector<Vector3f*> result;
  unsigned planesLen = planes.size();
  result.reserve(planesLen);
  for (unsigned ii = 0; ii < planesLen; ++ii) {
    Plane* p = planes[ii];
    // Check if parallel
    //    if (p->nor.cross(r->direction).isZero()) {
    //      result.push_back(NULL);
    //      continue;
    //    }
// Get intersection
    float lambda = p->pos.sub(r->origin).dot(p->nor)/r->direction.dot(p->nor);
    //float lambda = p->pos.dot(p->nor.sub(r->origin))/r->direction.dot(p->pos);
    if (lambda < 0) {
      result.push_back(NULL);
      continue;
    }
    //Vector3f* intersection = new Vector3f(r->origin.x,
    //                                      r->origin.y,
    //                                      r->origin.z);
    Vector3f* intersection = new Vector3f(r->origin.x + lambda*r->direction.x,
                                          r->origin.y + lambda*r->direction.y,
                                          r->origin.z + lambda*r->direction.z);

    result.push_back(intersection);
  }
  return result;
}

std::vector<Vector3f*> checkRayToTargets(Ray* r, std::vector<Target*> targets) {
  std::vector<Vector3f*> result;
  std::vector<Plane*> planes;
  unsigned targLen = targets.size();
  planes.reserve(targLen);

  for (unsigned ii = 0; ii < targLen; ++ii) {
    Plane* p = targets[ii]->getPlane();
    planes.push_back(p);
  }
  result = checkRayToPlanes(r, planes);
  for (unsigned ii = 0; ii < targLen; ++ii) {
    delete planes[ii];
  }

  for (unsigned ii = 0; ii < targLen; ++ii) {
    Vector3f* inter = result[ii];
    if (inter == 0) {
      delete result[ii];
      result[ii] = NULL;
      continue;
    }
    
    Target* targ = targets[ii];

    float disToTarg2 = (inter->x - targ->pos.x)*(inter->x - targ->pos.x) + 
                       (inter->y - targ->pos.y)*(inter->y - targ->pos.y) + 
                       (inter->z - targ->pos.z)*(inter->z - targ->pos.z);

    if (disToTarg2 > targ->rad*targ->rad) {
      delete result[ii];
      result[ii] = NULL;
    }
  }

  return result;
}
