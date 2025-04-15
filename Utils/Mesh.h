#pragma once

#include "primitive.h"
#include "triangle.h"

#include <vector>
#include <string>

namespace math {
  class Mesh : public primitive {
  public:
    std::vector<triangle*> triangles;

    Mesh(const std::string &filename,
      vec3 &translation,
      float scale,
      vec3 &rotation,
      Material &material
    );
    ~Mesh();

    vec3* hit(ray &ray) override;
    vec3 getNormal(vec3 point) override;
  };
} // namespace math