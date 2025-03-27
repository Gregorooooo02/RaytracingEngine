#pragma once

#include "ray.h"
#include "vec3.h"

namespace math {
    class triangle {
        public:
            vec3 vertices[3];
            vec3 normal;

            triangle();
            triangle(vec3, vec3, vec3);
            triangle(vec3&, vec3&, vec3&);
            ~triangle();
            triangle(const triangle&);

            bool hit(ray&);
    };
} // namespace math