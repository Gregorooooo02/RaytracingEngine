#include "Orthographic.h"

using namespace cam;

Orthographic::Orthographic(const math::vec3 &pos, const math::vec3 &tgt, const math::vec3 &upVec, float nearP, float farP, int samples)
    : Camera(pos, tgt, upVec, nearP, farP, samples) {}

math::ray Orthographic::generateRay(int pixelX, int pixelY, int imgWidth, int imgHeight) {
    float pixelWidth = 2.0f  / imgHeight;
    float pixelHeight = 2.0f / imgWidth;

    auto offset = sampleSquare();

    float x = -1.0f + (pixelX + offset.x) * pixelWidth;
    float y = 1.0f - (pixelY + offset.y) * pixelHeight;

    math::vec3 origin = position + math::vec3(x, y, 0.0f);
    math::vec3 dir = (target - position).normalize();

    math::ray ray(
        origin,
        dir
    );

    return ray;
}
