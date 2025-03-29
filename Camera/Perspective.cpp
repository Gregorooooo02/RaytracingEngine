#include "Perspective.h"

#include <cmath>
#include <iostream>

using namespace cam;

Perspective::Perspective(const math::vec3 &pos, const math::vec3 &tgt, const math::vec3 &upVec, float nearP, float farP, int samples, float fov)
    : Camera(pos, tgt, upVec, nearP, farP, samples), fov(fov) {
    math::vec3 u, v, w;
}

math::ray Perspective::generateRay(int pixelX, int pixelY, int imgWidth, int imgHeight) {
    math::vec3 u, v, w;
    math::vec3 origin = position;

    float focalLength = (target - position).len();
    float theta = fov * M_PI / 180.0f;
    float h = tan(theta / 2.0f);
    float aspectRatio = float(imgWidth) / float(imgHeight);

    float halfHeight = 2.0f * h * focalLength;
    float halfWidth = aspectRatio * halfHeight;

    w = (target - position).normalize();
    u = up.crossProduct(w).normalize();
    v = w.crossProduct(u);

    math::vec3 viewport_u = halfWidth * u;
    math::vec3 viewport_v = halfHeight * -v;

    math::vec3 pixelDeltaU = viewport_u / imgWidth;
    math::vec3 pixelDeltaV = viewport_v / imgHeight;

    math::vec3 upperLeft = origin - (w * focalLength) - viewport_u/2 - viewport_v/2;
    auto pixel00 = upperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);

    auto offset = sampleSquare();
    auto pixelSample = pixel00 + ((pixelX + offset.x) * pixelDeltaU) + ((pixelY + offset.y) * pixelDeltaV);

    math::vec3 direction = (pixelSample - origin);

    math::ray ray(
        origin,
        direction
    );

    return ray;
}