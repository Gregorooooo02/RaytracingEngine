#include "Camera.h"

using namespace cam;

Camera::Camera(const math::vec3& pos, const math::vec3& tgt, const math::vec3& upVec, float nearP, float farP) {
    position = pos;
    target = tgt;
    up = upVec;
    nearPlane = nearP;
    farPlane = farP;
}

Camera::Camera() : position(0, 0, 0), target(0, 0, -1), up(0, 1, 0), nearPlane(0.1f), farPlane(100.0f) {
    // Default constructor initializes the camera to a standard position and orientation
}