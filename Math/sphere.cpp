#include "sphere.h"
#include "ray.h"
#include "util.h"

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

bool sphere::hit(ray &ray) {
  vec3 oc = ray.o.substract(this->center);

  float a = ray.d.dotProduct(ray.d);
  float b = 2.0f * oc.dotProduct(ray.d);
  float c = oc.dotProduct(oc) - this->radius * this->radius;

  float discriminant = math::quadDiscr(a, b, c);

  return discriminant > 0;
}
