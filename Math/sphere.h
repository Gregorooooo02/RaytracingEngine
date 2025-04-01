#pragma once
#include "LightIntensity.h"
#include "primitive.h"
#include "ray.h"
#include "vec3.h"

namespace math {
  class sphere : public primitive {
    private:
      vec3* hit(ray &ray, float tMin, float tMax);
    public:
      vec3 center;
      float radius;
      sphere();
      sphere(vec3 &center,  float radius, Material &material);
      sphere(const sphere &sphere);
      vec3* hit(ray &ray);
      vec3 getNormal(vec3 point);
      ~sphere();
  };

}
