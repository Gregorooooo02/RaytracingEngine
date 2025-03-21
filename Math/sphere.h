#pragma once

#include "primitive.h"
#include "vec3.h"

namespace math {
  class sphere : primitive {
    public:
      vec3 center;
      float radius;
      sphere();
      sphere(vec3 &center,  float radius);
      ~sphere();
      bool hit(ray &ray);
  };

}
