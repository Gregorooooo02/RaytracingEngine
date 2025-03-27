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
            triangle(vec3, vec3, vec3, cam::LightIntensity color);
            triangle(vec3&, vec3&, vec3&, cam::LightIntensity color);
            ~triangle();
            triangle(const triangle&);
            bool hit(ray&);
    };
} // namespace math
