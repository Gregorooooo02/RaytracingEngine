#include "plane.h"
#include "LightIntensity.h"

#include <iostream>

using namespace math;

plane::plane() {
    this->a = 0.0f;
    this->b = 0.0f;
    this->c = 0.0f;
    this->d = 0.0f;
    this->normal = vec3();
    this->color = cam::LightIntensity();
}

plane::plane(float a, float b, float c, float d, cam::LightIntensity color) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->normal = vec3(a, b, c);
    this->color = color;
}

plane::plane(const vec3& normal, float d, cam::LightIntensity color) {
    this->a = normal.x;
    this->b = normal.y;
    this->c = normal.z;
    this->d = d;
    this->normal = normal;
    this->color = color;
}

plane::plane(vec3& normal, vec3& point, cam::LightIntensity color) {
    this->a = normal.x;
    this->b = normal.y;
    this->c = normal.z;
    this->d = -normal.dotProduct(point);
    this->normal = normal;
    this->point = point;
    this->color = color;
}

plane::plane(vec3& p1, vec3& p2, vec3& p3, cam::LightIntensity color) {
    vec3 temp = p3.substract(p1);
    this->normal = (p2.substract(p1)).crossProduct(temp).normalize();
    this->a = this->normal.x;
    this->b = this->normal.y;
    this->c = this->normal.z;
    this->d = -this->normal.dotProduct(p1);
    this->point = p1;
    this->color = color;
}

plane::plane(const plane& plane) {
    this->a = plane.a;
    this->b = plane.b;
    this->c = plane.c;
    this->d = plane.d;
    this->normal = plane.normal;
    this->point = plane.point;
    this->color = color;
}

plane::~plane() {}

bool plane::hit(ray& ray) {
    float denominator = this->normal.dotProduct(ray.d);
    if (denominator == 0) {
        return false;
    }

    float t = -(this->normal.dotProduct(ray.o) + this->d) / denominator;

    // Tymczasowe
    vec3 hitPoint = ray.point_at(t);
    std::cout << "Hit point: " << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << std::endl;

    return t >= 0;
}
