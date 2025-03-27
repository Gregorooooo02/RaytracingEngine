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

vec3 ray::point_at(float t) {
  vec3 copy_o = vec3(this->o);
  vec3 copy_d = vec3(this->d);

  return copy_o.add(copy_d.multiply(t));
}
