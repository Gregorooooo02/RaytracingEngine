#pragma once

#include "primitive.h"
#include "vec3.h"

namespace math {
  class sphere : public primitive {
    public:
      vec3 center;
      float radius;
      sphere();
      sphere(vec3 &center,  float radius);
      sphere(const sphere &sphere);
      ~sphere();
      bool hit(ray &ray, float tMin, float tMax) override;
  };

}
