#include "sphere.h"
#include "LightIntensity.h"
#include "ray.h"
#include "util.h"
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
  return this->hit(ray, std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
}

vec3* sphere::hit(ray &ray, float tMin, float tMax) {
  vec3 oc = ray.o.substract(this->center);

  float a = ray.d.dotProduct(ray.d);
  float b = oc.dotProduct(ray.d);
  float c = oc.dotProduct(oc) - this->radius * this->radius;

  float discriminant = math::quadDiscr(a, b, c);

  if (discriminant < 0) {
    // std::cout << "No hit" << std::endl;
    return nullptr;
  }

  float x1 = math::root(b, -discriminant, a);
  float x2 = math::root(b, discriminant, a);

  // // Tymczasowe
  // if (discriminant == 0) {
  //   std::cout << "Hit at t = " << x1 << std::endl;
  //   vec3 hitPoint = ray.point_at(x1);
  //
  //   std::cout << "Hit point: " << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << std::endl;
  // } else {
  //   std::cout << "Hit at t = " << x1 << " and t = " << x2 << std::endl;
  //   vec3 hitPoint1 = ray.point_at(x1);
  //   vec3 hitPoint2 = ray.point_at(x2);
  //
  //   std::cout << "Hit point 1: " << hitPoint1.x << ", " << hitPoint1.y << ", " << hitPoint1.z << std::endl;
  //   std::cout << "Hit point 2: " << hitPoint2.x << ", " << hitPoint2.y << ", " << hitPoint2.z << std::endl;
  // }

  vec3 result = ray.point_at(x1);
  vec3* resultPtr = new vec3(result);
  return resultPtr;
}

vec3 sphere::getNormal(vec3 point) {
  vec3 normal = (point - this->center).normalize();
  return normal.normalize();
}