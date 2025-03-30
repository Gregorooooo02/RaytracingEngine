#include "Orthographic.h"

using namespace cam;

Orthographic::Orthographic(const math::vec3 &pos, const math::vec3 &tgt, const math::vec3 &upVec, float nearP, float farP, int samples)
    : Camera(pos, tgt, upVec, nearP, farP, samples) {}

math::ray Orthographic::generateRay(int pixelX, int pixelY, int imgWidth, int imgHeight) {
    float aspectRatio = float(imgWidth) / float(imgHeight);

    float x_min, x_max, y_min, y_max;
    if (aspectRatio >= 1.0f) {
        x_min = -aspectRatio;
        x_max = aspectRatio;
        y_min = -1.0f;
        y_max = 1.0f;
    } else {
        x_min = -1.0f;
        x_max = 1.0f;
        y_min = -1.0f / aspectRatio;
        y_max = 1.0f / aspectRatio;
    }

    float pixelWidth = (x_max - x_min) / float(imgWidth);
    float pixelHeight = (y_max - y_min) / float(imgHeight);

    auto offset = sampleSquare();
    float x = x_min + (pixelX + offset.x) * pixelWidth;
    float y = y_max - (pixelY + offset.y) * pixelHeight;

    math::vec3 origin = position + math::vec3(x, y, 0.0f);
    math::vec3 dir = (target - position).normalize();

    math::ray ray(
        origin,
        dir
    );

    return ray;
}
