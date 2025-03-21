#include "sphere.h"
#include "ray.h"
#include "util.h"
#include <cmath>
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

sphere::sphere(const sphere &sphere) {
  this->center = sphere.center;
  this->radius = sphere.radius;
}

sphere::~sphere() {}

bool sphere::hit(ray &ray, float tMin, float tMax) {
  vec3 oc = ray.o.substract(this->center);

  float a = ray.d.dotProduct(ray.d);
  float b = 2.0f * oc.dotProduct(ray.d);
  float c = oc.dotProduct(oc) - this->radius * this->radius;

  float discriminant = math::quadDiscr(a, b, c);

  if (discriminant < 0) {
    return false;
  }

  float x1 = math::root(b, (discriminant * -1), a);
  float x2 = math::root(b, discriminant, a);

  return (x1 > tMin && x1 < tMax) || (x2 > tMin && x2 < tMax);
}
