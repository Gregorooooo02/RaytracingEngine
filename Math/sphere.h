#pragma once
#include "ray.h"
#include "vec3.h"

//TODO: implementacja hit()
namespace math {
  class sphere {
    public:
      vec3 center;
      float radius;
      sphere();
      sphere(vec3 &center,  float radius);
      ~sphere();
      bool hit(ray ray, float t_min, float t_max);
  };

}
