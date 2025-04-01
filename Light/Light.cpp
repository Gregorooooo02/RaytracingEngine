#include "Light.h"

using namespace licht;

Light::Light(cam::LightIntensity intensity) : intensity(intensity) {}

Light::Light() : intensity(cam::LightIntensity(0, 0, 0)) {}
