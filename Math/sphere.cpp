#include "sphere.h"
#include <stdexcept>

using namespace math;

sphere::sphere() {
  this->center = vec3();
  this->radius = 0.0f;
}

sphere::sphere(vec3 &center, float radius) {
  this->center = center;

  if (radius < 0) {
    throw std::invalid_argument("radius has to be positive");
  }

  this->radius = radius;
}
