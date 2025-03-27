#include "Perspective.h"

using namespace cam;

Perspective::Perspective(const math::vec3 &pos, const math::vec3 &tgt, const math::vec3 &upVec, float nearP, float farP, float fov)
    : Camera(pos, tgt, upVec, nearP, farP), fov(fov) {}

math::ray Perspective::generateRay(int pixelX, int pixelY, int imgWidth, int imgHeight) {
    float a = (pixelX + 0.5f) / imgWidth;
    float b = (pixelY + 0.5f) / imgHeight;

    math::vec3 w = (position - target).normalize();
    math::vec3 u = up.crossProduct(w).normalize();
    math::vec3 v = w.crossProduct(u).normalize();
}