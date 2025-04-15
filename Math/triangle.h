#pragma once

#include "LightIntensity.h"
#include "primitive.h"
#include "ray.h"
#include "vec3.h"

namespace math {
    class triangle : public primitive {
        public:
            vec3 vertices[3];
            vec3 normal;
            triangle();
            triangle(vec3, vec3, vec3, Material&);
            triangle(const vec3 &v1, const vec3 &v2, const vec3 &v3, const Material &material);
            triangle(const vec3 &v1, const vec3 &v2, const vec3 &v3, const vec3 &n1, const vec3 &n2, const vec3 &n3, const Material &material);
            ~triangle();
            triangle(const triangle&);
            vec3* hit(ray&);
            vec3 getNormal(vec3 point);
    };
} // namespace math
