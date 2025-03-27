#include "triangle.h"
#include "LightIntensity.h"
#include <cmath>

using namespace math;

triangle::triangle() {
    for (int i = 0; i < 3; i++) {
        this->vertices[i] = vec3();
    }
    this->normal = vec3();
    this->color = cam::LightIntensity();
}

triangle::triangle(vec3 v1, vec3 v2, vec3 v3, cam::LightIntensity color) {
    this->vertices[0] = v1;
    this->vertices[1] = v2;
    this->vertices[2] = v3;
    this->color = color;

    vec3 temp = v3.substract(v1);
    this->normal = (v2.substract(v1)).crossProduct(temp).normalize();
}

triangle::triangle(vec3& v1, vec3& v2, vec3& v3, cam::LightIntensity color) {
    this->vertices[0] = v1;
    this->vertices[1] = v2;
    this->vertices[2] = v3;
    this->color = color;

    vec3 temp = v3.substract(v1);
    this->normal = (v2.substract(v1)).crossProduct(temp).normalize();
}

triangle::~triangle() = default;

triangle::triangle(const triangle& t) {
    for (int i = 0; i < 3; i++) {
        this->vertices[i] = t.vertices[i];
    }
    this->normal = t.normal;
    this->color = t.color;
}

bool triangle::hit(ray& ray) {
    vec3 v1v0 = this->vertices[1] - this->vertices[0];
    vec3 v2v0 = this->vertices[2] - this->vertices[0];

    vec3 normal = v1v0.crossProduct(v2v0).normalize();

    float t;
    float d = -normal.dotProduct(this->vertices[0]);
    float denominator = normal.dotProduct(ray.d);
    if (fabs(denominator) < 1e-6) {
        if (fabs(normal.dotProduct(ray.o) + d) < 1e-6) {
            float t_candidate = std::numeric_limits<float>::max();
            bool found = false;

            auto intersectEdge = [&](const vec3& vA, const vec3& vB) {
                float A1 = ray.d.x;
                float B1 = -(vB.x - vA.x);
                float C1 = vA.x - ray.o.x;
                float A2 = ray.d.y;
                float B2 = -(vB.y - vA.y);
                float C2 = vA.y - ray.o.y;
                float det = A1 * B2 - A2 * B1;
                if (fabs(det) < 1e-6) return; // Linie równoległe
                float t_temp = (C1 * B2 - C2 * B1) / det;
                float s_temp = (A1 * C2 - A2 * C1) / det;
                if (t_temp >= 0 && s_temp >= 0 && s_temp <= 1) {

                    if (t_temp < t_candidate) {
                        t_candidate = t_temp;
                        found = true;
                    }
                }
            };

            intersectEdge(this->vertices[0], this->vertices[1]);
            intersectEdge(this->vertices[1], this->vertices[2]);
            intersectEdge(this->vertices[2], this->vertices[0]);

            if (found) {
                t = t_candidate;
                return true;
            }
        }

        return false;
    }
    t = -(normal.dotProduct(ray.o) + d) / denominator;

    if (t < 0) {
        return false;
    }

    vec3 hitPoint = ray.o + ray.d * t;

    // Test krawędzi 0
    vec3 v0p = hitPoint - this->vertices[0];
    vec3 ne = v1v0.crossProduct(v0p);
    if (normal.dotProduct(ne) <= 0) {
        return false;
    }

    // Test krawędzi 1
    vec3 v2v1 = this->vertices[2] - this->vertices[1];
    vec3 v1p = hitPoint - this->vertices[1];
    ne = v2v1.crossProduct(v1p);
    if (normal.dotProduct(ne) <= 0) {
        return false;
    }

    // Test krawędzi 2
    vec3 v0v2 = this->vertices[0] - this->vertices[2];
    vec3 v2p = hitPoint - this->vertices[2];
    ne = v0v2.crossProduct(v2p);
    if (normal.dotProduct(ne) <= 0) {
        return false;
    }

    return true;
}
