#pragma once

#include "Camera.h"

namespace cam {
    class Orthographic : public Camera {
    public:
        Orthographic(const math::vec3& pos, const math::vec3& tgt, const math::vec3& upVec, float nearP, float farP, int samples = 10);

        math::ray generateRay(int pixelX, int pixelY, int imgWidth, int imgHeight) override;
    };
} // namespace cam