#pragma once
#include "LightIntensity.h"
#include "primitive.h"
#include "vec3.h"
#include "ray.h"

namespace math {
    class plane : public primitive {
        public:
            plane();
            plane(float, float, float, float, Material&);
            plane(const vec3&, float, Material&);
            plane(vec3&, vec3&, Material&);
            plane(vec3&, vec3&, vec3&, Material&);
            plane(const plane&);
            ~plane();
            vec3* hit(ray&);
            vec3 getNormal(vec3 point);
        private:
            float a, b, c, d;
            vec3 normal;
            vec3 point;

    };
} // namespace math
