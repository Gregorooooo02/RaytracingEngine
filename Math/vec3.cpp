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

vec3& vec3::operator=(const vec3 &vec) {
  this->x = vec.x;
  this->y = vec.y;
  this->z = vec.z;

  return *this;
}

vec3::~vec3() {}

vec3 vec3::add(const vec3 &vec) const {
  vec3 result = *this;
  result.x += vec.x;
  result.y += vec.y;
  result.z += vec.z;

  return result;
}

vec3 vec3::substract(const vec3 &vec) const {
  vec3 result = *this;
  result.x -= vec.x;
  result.y -= vec.y;
  result.z -= vec.z;

  return result;
}

vec3 vec3::multiply(const float multiplier) const {
  vec3 result = *this;
  result.x *= multiplier;
  result.y *= multiplier;
  result.z *= multiplier;

  return result;
}

vec3 vec3::divide(const float divider) const {
  vec3 result = *this;
  if (divider == 0.0f) {
    throw std::invalid_argument("cant divide by 0");
  }

  result.x /= divider;
  result.y /= divider;
  result.z /= divider;

  return result;
}

float vec3::len() {
  return (float)std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) +
                          std::pow(this->z, 2));
}

vec3 vec3::normalize() {
  vec3 result = *this;
  float length = result.len();

  if (length == 0.0f) {
    throw std::invalid_argument("cant divide by 0");
  }

  return result/length;
}

float vec3::dotProduct(vec3 &vec) {
  vec3 result = *this;
  return result.x * vec.x + result.y * vec.y + result.z * vec.z;
}

vec3 vec3::crossProduct(vec3 &vec) {
  vec3 result(this->y * vec.z - this->z * vec.y,
              this->z * vec.x - this->x * vec.z,
              this->x * vec.y - this->y * vec.x);

  return result;
}

vec3 vec3::rotate(float angle, vec3& axis) {
  float angleRad = angle * M_PI / 180.0f;
  quaternion p(0, *this);

  vec3 normalizedAxis = axis.normalize();
  quaternion q(angleRad, normalizedAxis);
  q.convertToUnitNorm();

  quaternion qInverse = q.inverse();
  quaternion rotatedVector = q.multiply(p).multiply(qInverse);

  return rotatedVector.v;
}

vec3 vec3::reflect(vec3 &vec) {
  vec3 result = *this;
  float dotProduct = result.dotProduct(vec);
  return result - vec.multiply(2 * dotProduct);
}

// Operators
vec3 math::operator+(const vec3 &v1, const vec3 &v2) {
  return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

vec3 math::operator-(const vec3 &v1, const vec3 &v2) {
  return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

vec3 math::operator-(const vec3 &v) {
  return {-v.x, -v.y, -v.z};
}

vec3 math::operator*(const vec3 &v, float scalar) {
  return {v.x * scalar, v.y * scalar, v.z * scalar};
}

vec3 math::operator*(float scalar, const vec3 &v) {
  return {v.x * scalar, v.y * scalar, v.z * scalar};
}

vec3 math::operator/(const vec3 &v, float scalar) {
  if (scalar == 0.0f) {
    throw std::invalid_argument("cant divide by 0");
  }
  return {v.x / scalar, v.y / scalar, v.z / scalar};
}