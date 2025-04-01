#include "Material.h"

Material::Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse, const cam::LightIntensity& specular, float shininess, float reflection)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), reflection(reflection) {}

Material::Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse, const cam::LightIntensity& specular, float shininess)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), reflection(0.0f) {}

Material::Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse, const cam::LightIntensity& specular)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(0.0f), reflection(0.0f) {}

Material::Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse)
    : ambient(ambient), diffuse(diffuse), specular(cam::LightIntensity(0.0f, 0.0f, 0.0f)), shininess(0.0f), reflection(0.0f) {}

Material::Material(const cam::LightIntensity& ambient)
    : ambient(ambient), diffuse(cam::LightIntensity(0.0f, 0.0f, 0.0f)), specular(cam::LightIntensity(0.0f, 0.0f, 0.0f)), shininess(0.0f), reflection(0.0f) {}

Material::Material() {
    this->ambient = cam::LightIntensity(0.0f, 0.0f, 0.0f);
    this->diffuse = cam::LightIntensity(0.0f, 0.0f, 0.0f);
    this->specular = cam::LightIntensity(0.0f, 0.0f, 0.0f);
    this->shininess = 0.0f;
    this->reflection = 0.0f;
}