#pragma once

#include "vec3.h"

namespace cam {
    class LightIntensity {
        public:
        double r, g, b;

        LightIntensity(double R, double G, double B);
        LightIntensity(double R, double G);
        LightIntensity(double R);
        LightIntensity();
        LightIntensity(const LightIntensity& other);

        double getR() const;
        double getG() const;
        double getB() const;

        int red() const;
        int green() const;
        int blue() const;

        // Operators
        LightIntensity operator+(const LightIntensity& other) const;
        LightIntensity operator+(math::vec3 rgb) const;

        LightIntensity operator-(const LightIntensity& other) const;
        LightIntensity operator-(math::vec3 rgb) const;

        LightIntensity operator*(const LightIntensity& other) const;
        LightIntensity operator*(const float& scalar) const;

        LightIntensity operator/(const LightIntensity& other) const;
        LightIntensity operator/(const float& scalar) const;
    };
} // namespace cam