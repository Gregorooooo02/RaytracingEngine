#include "vec3.h"
#include "quaternion.h"

#include <cmath>
#include <stdexcept>

using namespace math;

vec3::vec3() {
  this->x = 0.0f;
  this->y = 0.0f;
  this->z = 0.0f;
}

vec3::vec3(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

vec3::vec3(const vec3 &vec) {
  this->x = vec.x;
  this->y = vec.y;
  this->z = vec.z;
}

vec3::~vec3() {}

vec3& vec3::add(vec3 &vec) {
  this->x += vec.x;
  this->y += vec.y;
  this->z += vec.z;

  return *this;
}

vec3& vec3::substract(vec3 &vec) {
  this->x -= vec.x;
  this->y -= vec.y;
  this->z -= vec.z;

  return *this;
}

vec3& vec3::multiply(float multiplier) {
  this->x *= multiplier;
  this->y *= multiplier;
  this->z *= multiplier;

  return *this;
}

vec3& vec3::divide(float divider) {
  if (divider == 0.0f) {
    throw std::invalid_argument("cant divide by 0");
  }

  this->x /= divider;
  this->y /= divider;
  this->z /= divider;

  return *this;
}

float vec3::len() {
  return (float)std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) +
                          std::pow(this->z, 2));
}

vec3& vec3::normalize() {
  float length = this->len();

  if (length == 0.0f) {
    throw std::invalid_argument("cant divide by 0");
  }

  this->divide(length);

  return *this;
}

float vec3::dotProduct(vec3 &vec) {
  return this->x * vec.x + this->y * vec.y + this->z * vec.z;
}

vec3 vec3::crossProduct(vec3 &vec) {
  vec3 result(this->y * vec.z - this->z * vec.y,
              this->z * vec.x - this->x * vec.z,
              this->x * vec.y - this->y * vec.x);

  return result;
}

vec3 vec3::rotate(float angle, vec3& axis) {
  quaternion p(0, *this);

  axis.normalize();

  quaternion q(angle, axis);
  q.convertToUnitNorm();

  quaternion qInverse = q.inverse();
  quaternion rotatedVector = q.multiply(p).multiply(qInverse);

  return rotatedVector.v;
}
