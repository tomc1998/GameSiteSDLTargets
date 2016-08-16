#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector3f {
public:
  float x, y, z;
  Vector3f();
  Vector3f(float _x, float _y, float _z);
  float dot(const Vector3f& vec);
  Vector3f add(const Vector3f& vec) const;
  Vector3f sub(const Vector3f& vec) const;
};

#endif
