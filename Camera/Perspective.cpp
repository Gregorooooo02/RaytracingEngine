#include "Perspective.h"

#include <cmath>

using namespace cam;

Perspective::Perspective(const math::vec3 &pos, const math::vec3 &tgt, const math::vec3 &upVec, float nearP, float farP, float fov)
    : Camera(pos, tgt, upVec, nearP, farP), fov(fov) {}

math::ray Perspective::generateRay(int pixelX, int pixelY, int imgWidth, int imgHeight) {
    math::vec3 u, v, w;
    math::vec3 origin = position;

    float focalLength = (target - position).len();
    float theta = fov * M_PI / 180.0f;
    float aspectRatio = float(imgWidth) / float(imgHeight);

    float h = tan(theta / 2.0f);
    float halfHeight = 2.0f * h * focalLength;
    float halfWidth = aspectRatio * halfHeight;

    w = (target - position).normalize();
    u = up.crossProduct(w).normalize();
    v = w.crossProduct(u);

    math::vec3 viewport_u = halfWidth * u;
    math::vec3 viewport_v = halfHeight * -v;

    math::vec3 pixelDeltaU = viewport_u / imgWidth;
    math::vec3 pixelDeltaV = viewport_v / imgHeight;

    math::vec3 lowerLeft = origin - (w * focalLength) - viewport_u/2 - viewport_v/2;

    float a = float(pixelX + 0.5f) / float(imgWidth);
    float b = float(pixelY + 0.5f) / float(imgHeight);

    math::vec3 pixelPos = lowerLeft + a * viewport_u + b * viewport_v;
    math::vec3 direction = (pixelPos - origin).normalize();

    math::ray ray(
        origin,
        direction
    );

    return ray;
}