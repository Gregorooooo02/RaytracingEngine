#pragma once

#include "Camera.h"

namespace cam {
    class Perspective : public Camera {
    public:
        float fov; // Field of view in degrees

        Perspective(const math::vec3 &pos, const math::vec3 &tgt, const math::vec3 &upVec, float nearP, float farP, float fov);

        math::ray generateRay(int pixelX, int pixelY, int imgWidth, int imgHeight) override;
    };
} // namespace cam
