#pragma once

#include "LightIntensity.h"

class Material {
public:
    cam::LightIntensity ambient;
    cam::LightIntensity diffuse;
    cam::LightIntensity specular;
    float shininess;
    float reflection;

    Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse, const cam::LightIntensity& specular, float shininess, float reflection);
    Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse, const cam::LightIntensity& specular, float shininess);
    Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse, const cam::LightIntensity& specular);
    Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse);
    Material(const cam::LightIntensity& ambient);
    Material();
    Material(const Material& other);
    ~Material() = default;
};