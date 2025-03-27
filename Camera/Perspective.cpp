#include "Perspective.h"

#include <cmath>

using namespace cam;

Perspective::Perspective(const math::vec3 &pos, const math::vec3 &tgt, const math::vec3 &upVec, float nearP, float farP, float fov)
    : Camera(pos, tgt, upVec, nearP, farP), fov(fov) {}

math::ray Perspective::generateRay(int pixelX, int pixelY, int imgWidth, int imgHeight) {
    float a = (pixelX + 0.5f) / imgWidth;
    float b = (pixelY + 0.5f) / imgHeight;

    math::vec3 w = (position - target).normalize();
    math::vec3 u = up.crossProduct(w).normalize();
    math::vec3 v = w.crossProduct(u);

    float aspectRatio = static_cast<float>(imgWidth) / static_cast<float>(imgHeight);
    float theta = fov * M_PI / 180.0f;

    float halfHeight = tan(theta/2.0f);
    float halfWidth = aspectRatio * halfHeight;

    math::vec3 lower_left_corner = position - halfWidth * u - halfHeight * v - w;
    math::vec3 horizontal = 2.0f * halfWidth * u;
    math::vec3 vertical = 2.0f * halfHeight * v;

    math::vec3 pointOnPlane = lower_left_corner + a * horizontal + b * vertical;
    math::vec3 direction = (pointOnPlane - position).normalize();

    return {position, direction};
}