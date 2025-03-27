#pragma once

#include "vec3.h"
#include "ray.h"

namespace cam {
    class Camera {
    public:
        math::vec3 position;
        math::vec3 target;
        math::vec3 up;
        float nearPlane;
        float farPlane;

        Camera(const math::vec3& pos, const math::vec3& tgt, const math::vec3& upVec, float nearP, float farP);
        Camera();

        virtual math::ray generateRay(int pixelX, int pixelY, int imgWidth, int imgHeight) = 0;
        virtual ~Camera() = default;
    };
} // namespace cam