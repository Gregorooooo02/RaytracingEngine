#include "Material.h"

Material::Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse, const cam::LightIntensity& specular, float shininess, float reflection, float refraction, float ior)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), reflection(reflection), refraction(refraction), ior(ior) {}

Material::Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse, const cam::LightIntensity& specular, float shininess)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), reflection(0.0f) {}

Material::Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse, const cam::LightIntensity& specular)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(0.0f), reflection(0.0f) {}

Material::Material(const cam::LightIntensity& ambient, const cam::LightIntensity& diffuse)
    : ambient(ambient), diffuse(diffuse), specular(cam::LightIntensity(0.0f, 0.0f, 0.0f)), shininess(0.0f), reflection(0.0f) {}

Material::Material(const cam::LightIntensity& ambient)
    : ambient(ambient), diffuse(cam::LightIntensity(0.0f, 0.0f, 0.0f)), specular(cam::LightIntensity(0.0f, 0.0f, 0.0f)), shininess(0.0f), reflection(0.0f) {}

Material::Material() {
    this->ambient = cam::LightIntensity(0.01f, 0.01f, 0.01f);
    this->diffuse = cam::LightIntensity(1.0f, 1.0f, 1.0f);
    this->specular = cam::LightIntensity(0.0f, 0.0f, 0.0f);
    this->shininess = 0.0f;
    this->reflection = 0.0f; // Amount of reflection [0.0f - 1.0f]
    this->refraction = 0.0f; // Amount of refraction [0.0f - 1.0f]
    this->ior = 1.0f; // Default index of refraction for air
}