#include "vec3.h"
#include <cmath>
#include <stdexcept>

Vec3::Vec3() {
  this->x = 0.0f;
  this->y = 0.0f;
  this->z = 0.0f;
}

Vec3::Vec3(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vec3::Vec3(Vec3 &vec) {
  this->x = vec.x;
  this->y = vec.y;
  this->z = vec.z;
}

Vec3::~Vec3() {}

void Vec3::add(Vec3 &vec) {
  this->x += vec.x;
  this->y += vec.y;
  this->z += vec.z;
}

void Vec3::substract(Vec3 &vec) {
  this->x -= vec.x;
  this->y -= vec.y;
  this->z -= vec.z;
}

void Vec3::multiply(float multiplier) {
  this->x *= multiplier;
  this->y *= multiplier;
  this->z *= multiplier;
}

void Vec3::divide(float divider) {
  if (divider == 0.0f) {
    throw std::invalid_argument("cant divide by 0");
  }

  this->x /= divider;
  this->y /= divider;
  this->z /= divider;
}

float Vec3::len() {
  return (float)std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) +
                          std::pow(this->z, 2));
}

void Vec3::normalize() {
  float length = this->len();

  if (length == 0.0f) {
    throw std::invalid_argument("cant divide by 0");
  }

  this->divide(length);
}

float Vec3::dot_product(Vec3 &vec) {
  return this->x * vec.x + this->y * vec.y + this->z * vec.z;
}

Vec3 Vec3::cross_product(Vec3 &vec) {
  Vec3 result(this->y * vec.z - this->z * vec.y,
              this->z * vec.x - this->x * vec.z,
              this->x * vec.y - this->y * vec.x);

  return result;
}
