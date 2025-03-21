#include "quaternion.h"
#include "util.h"
#include <cmath>

using namespace math;

quaternion::quaternion(float s, vec3& v) : s(s), v(v) {}

quaternion::~quaternion() {}

quaternion::quaternion(const quaternion& q) {
    this->s = q.s;
    this->v = q.v;
}

quaternion& quaternion::operator=(const quaternion& q) {
    this->s = q.s;
    this->v = q.v;

    return *this;
}

quaternion quaternion::add(quaternion& q){
    this->s += q.s;
    this->v.add(q.v);

    return *this;
}

quaternion quaternion::substract(quaternion& q){
    this->s -= q.s;
    this->v.substract(q.v);

    return *this;
}

quaternion quaternion::multiply(quaternion& q) {
    float scalar = this->s * q.s - this->v.dotProduct(q.v);
    vec3 temp1 = this->v.multiply(q.s);
    vec3 temp2 = q.v.multiply(this->s);
    vec3 temp3 = this->v.crossProduct(q.v);

    temp1.add(temp2);
    temp1.add(temp3);

    this->s = scalar;
    this->v = temp1;

    return *this;
}

quaternion quaternion::multiply(float scalar) {
    this->s *= scalar;
    this->v.multiply(scalar);

    return *this;
}

float quaternion::norm() {
    float scalar = this->s * this->s;
    float vec = this->v.dotProduct(this->v);

    return std::sqrt(scalar + vec);
}

void quaternion::normalize() {
    if (this->norm() != 0) {
        float normValue = 1/this->norm();

        this->s *= normValue;
        this->v.multiply(normValue);
    }
}

quaternion quaternion::conjugate() {
    this->v.multiply(-1);
    return *this;
}

quaternion quaternion::inverse() {
    float absValue = this->norm();
    absValue *= absValue;
    absValue = 1/absValue;

    quaternion conjugate = this->conjugate();

    float scalar = conjugate.s * absValue;
    vec3 img = conjugate.v.multiply(absValue);

    return quaternion(scalar, img);
}

void quaternion::convertToUnitNorm() {
    float angle = degreesToRadians(this->s);
    v.normalize();

    this->s = std::cosf(angle/2);
    this->v.multiply(std::sinf(angle/2));
}
