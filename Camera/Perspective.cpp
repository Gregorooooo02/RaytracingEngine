#include "Perspective.h"

#include <cmath>

using namespace cam;

Perspective::Perspective(const math::vec3 &pos, const math::vec3 &tgt, const math::vec3 &upVec, float nearP, float farP, float fov)
    : Camera(pos, tgt, upVec, nearP, farP), fov(fov) {}

math::ray Perspective::generateRay(int pixelX, int pixelY, int imgWidth, int imgHeight) {
    math::vec3 u, v, w;
    math::vec3 origin = position;

    float focalLength = (position - target).len();
    float theta = fov * M_PI / 180.0f;
    float aspectRatio = float(imgWidth) / float(imgHeight);

    float halfHeight = 2.0f * tan(theta / 2.0f) * focalLength;
    float halfWidth = aspectRatio * halfHeight;

    w = (position - target).normalize();
    u = up.crossProduct(w).normalize();
    v = w.crossProduct(u);

    math::vec3 horizontal = -halfWidth * u;
    math::vec3 vertical = halfHeight * v;

    math::vec3 pixelDeltaU = horizontal / float(imgWidth);
    math::vec3 pixelDeltaV = vertical / float(imgHeight);

    math::vec3 upperLeft = origin - (w * focalLength) - horizontal/2 - vertical/2;

    float s = float(pixelX) / float(imgWidth);
    float t = float(pixelY) / float(imgHeight);

    math::vec3 pixelPos = upperLeft + s * horizontal + t * vertical;
    math::vec3 direction = pixelPos - origin;

    math::ray ray(
        origin,
        direction
    );

    return ray;
}