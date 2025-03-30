#include "Camera.h"
#include "util.h"

using namespace cam;

Camera::Camera(const math::vec3& pos, const math::vec3& tgt, const math::vec3& upVec, float nearP, float farP, int samples) {
    position = pos;
    target = tgt;
    up = upVec;
    nearPlane = nearP;
    farPlane = farP;
    samplesCount = samples;
}

Camera::Camera()
: position(0, 0, 0), target(0, 0, -1), up(0, 1, 0), nearPlane(0.1f), farPlane(100.0f), samplesCount(10) {
    // Default constructor initializes the camera to a standard position and orientation
}

// Returns a vec3 with random x and y values in the range [-0.5, 0.5]
math::vec3 Camera::sampleSquare() const {
    return {math::random_float() - 0.5f, math::random_float() - 0.5f, 0};
}