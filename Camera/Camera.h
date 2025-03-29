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
        int samplesCount = 10;

        Camera(const math::vec3& pos, const math::vec3& tgt, const math::vec3& upVec, float nearP, float farP, int samples = 10);
        Camera();

        math::vec3 sampleSquare() const;

        virtual math::ray generateRay(int pixelX, int pixelY, int imgWidth, int imgHeight) = 0;
        virtual ~Camera() = default;
    };
} // namespace cam