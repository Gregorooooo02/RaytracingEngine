#include "sphere.h"
#include "LightIntensity.h"
#include "ray.h"
#include "util.h"
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace math;

sphere::sphere() {
  this->center = vec3();
  this->radius = 0.0f;
  this->material = Material();
}

sphere::sphere(vec3 &center, float radius, Material &material) {
  this->center = center;

  if (radius < 0) {
    throw std::invalid_argument("radius has to be positive");
  }

  this->radius = radius;
  this->material = material;
}

sphere::~sphere() {}

sphere::sphere(const sphere &sphere) {
  this->center = sphere.center;
  this->radius = sphere.radius;
  this->material = sphere.material;
}

vec3* sphere::hit(ray &ray) {
  vec3 oc = ray.o.substract(this->center);

  float a = ray.d.dotProduct(ray.d);
  float b = 2 * oc.dotProduct(ray.d);
  float c = oc.dotProduct(oc) - this->radius * this->radius;

  float discriminant = (b * b) - (4 * a * c);

  if (discriminant < 0) {
    return nullptr;
  }

  float x1 = (-b - std::sqrt(discriminant)) / (2 * a);
  float x2 = (-b + std::sqrt(discriminant)) / (2 * a);
  float x;

  if (x1 > 0) {
    x = x1;
  } else if (x2 > 0) {
    x = 2;
  } else {
    return nullptr;
  }

  vec3 result = ray.point_at(x);
  vec3* resultPtr = new vec3(result);
  return resultPtr;
}

vec3 sphere::getNormal(vec3 point) {
  vec3 normal = (point - this->center).normalize();
  return normal;
}
