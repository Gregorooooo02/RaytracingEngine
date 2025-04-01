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

LightIntensity::LightIntensity(const LightIntensity& other) {
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
}

double LightIntensity::getR() const {
    if (this->r < 0) {
        return 0;
    }
    else if (this->r > 1) {
        return 1;
    }

    return this->r;
}

double LightIntensity::getG() const {
    if (this->g < 0) {
        return 0;
    }
    else if (this->g > 1) {
        return 1;
    }

    return this->g;
}

double LightIntensity::getB() const {
    if (this->b < 0) {
        return 0;
    }
    else if (this->b > 1) {
        return 1;
    }

    return this->b;
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

LightIntensity LightIntensity::operator+(math::vec3 rgb) const {
    return {this->r + rgb.x, this->g + rgb.y, this->b + rgb.z};
}


LightIntensity LightIntensity::operator-(const LightIntensity& other) const {
    return {this->r - other.r, this->g - other.g, this->b - other.b};
}

LightIntensity LightIntensity::operator-(math::vec3 rgb) const {
    return {this->r - rgb.x, this->g - rgb.y, this->b - rgb.z};
}

LightIntensity LightIntensity::operator*(const LightIntensity& other) const {
    return {this->r * other.r, this->g * other.g, this->b * other.b};
}

LightIntensity LightIntensity::operator*(const float& scalar) const {
    return {this->r * scalar, this->g * scalar, this->b * scalar};
}

LightIntensity LightIntensity::operator/(const LightIntensity& other) const {
    if (other.r == 0 || other.g == 0 || other.b == 0) {
        throw std::invalid_argument("Division by zero in LightIntensity");
    }
    return {this->r / other.r, this->g / other.g, this->b / other.b};
}

LightIntensity LightIntensity::operator/(const float &scalar) const {
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero in LightIntensity");
    }
    return {this->r / scalar, this->g / scalar, this->b / scalar};
}

