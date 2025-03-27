#pragma once
#include "primitive.h"
#include "ray.h"
#include "vec3.h"

namespace math {
  class sphere : public primitive {
    private:
      bool hit(ray &ray, float tMin, float tMax);
    public:
      vec3 center;
      float radius;
      sphere();
      sphere(vec3 &center,  float radius);
      sphere(const sphere &sphere);
      bool hit(ray &ray);
      ~sphere();
  };

}
