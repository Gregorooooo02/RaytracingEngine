#include "LightIntensity.h"

#include <algorithm>

using namespace cam;

LightIntensity::LightIntensity(double R, double G, double B) {
    this->r = R;
    this->g = G;
    this->b = B;
}

LightIntensity::LightIntensity(double R, double G) {
    this->r = R;
    this->g = G;
    this->b = 0.0;
}

LightIntensity::LightIntensity(double R) {
    this->r = R;
    this->g = 0.0;
    this->b = 0.0;
}

LightIntensity::LightIntensity() {
    this->r = 0.0;
    this->g = 0.0;
    this->b = 0.0;
}

int LightIntensity::red() const {
    return std::clamp(static_cast<int>(this->r * 255), 0, 255);
}

int LightIntensity::green() const {
    return std::clamp(static_cast<int>(this->g * 255), 0, 255);
}

int LightIntensity::blue() const {
    return std::clamp(static_cast<int>(this->b * 255), 0, 255);
}

LightIntensity LightIntensity::operator+(const LightIntensity& other) const {
    return {this->r + other.r, this->g + other.g, this->b + other.b};
}

LightIntensity LightIntensity::operator-(const LightIntensity& other) const {
    return {this->r - other.r, this->g - other.g, this->b - other.b};
}

LightIntensity LightIntensity::operator*(const LightIntensity& other) const {
    return {this->r * other.r, this->g * other.g, this->b * other.b};
}

LightIntensity LightIntensity::operator/(const LightIntensity& other) const {
    return {this->r / other.r, this->g / other.g, this->b / other.b};
}

LightIntensity LightIntensity::operator/(const float &scalar) const {
    return {this->r / scalar, this->g / scalar, this->b / scalar};
}

