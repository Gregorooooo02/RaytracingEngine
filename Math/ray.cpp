#include "ray.h"

using namespace math;

ray::ray() {
  this->o = vec3();
  this->d = vec3();
}

ray::ray(vec3 &o, vec3 &d) {
  this->o = o;
  this->d = d;
}

vec3 ray::hit_at(float t) { return this->o.add(this->d.multiply(t)); }
