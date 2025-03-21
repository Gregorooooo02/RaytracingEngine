#pragma once

#include "primitive.h"
#include "vec3.h"

namespace math {
    class triangle : primitive {
        public:
            vec3 vertices[3];
            vec3 normals[3];

            triangle();
            triangle(vec3&, vec3&, vec3&);
            triangle(vec3&, vec3&, vec3&, vec3&, vec3&, vec3&);
            ~triangle();
            triangle(const triangle&);

            bool hit(ray&);
    };
} // namespace math