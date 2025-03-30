#pragma once

namespace cam {
    class LightIntensity {
        public:
        double r, g, b;

        LightIntensity(double R, double G, double B);
        LightIntensity(double R, double G);
        LightIntensity(double R);
        LightIntensity();

        int red() const;
        int green() const;
        int blue() const;

        // Operators
        LightIntensity operator+(const LightIntensity& other) const;
        LightIntensity operator-(const LightIntensity& other) const;
        LightIntensity operator*(const LightIntensity& other) const;
        LightIntensity operator/(const LightIntensity& other) const;
        LightIntensity operator/(const float& scalar) const;
    };
} // namespace cam