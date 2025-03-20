#include "ray.h"

using namespace math;

ray::ray() {
  this->origin = vec3();
  this->destination = vec3();
}

ray::ray(vec3 &origin, vec3 &destination) {
  this->origin = origin;
  this->destination = destination;
}

vec3 ray::point_at(float t) {
  vec3 o(this->origin);
  vec3 d(this->destination);
  d.multiply(t);
  o.add(d);
  return o;
}

ray::~ray() {};
