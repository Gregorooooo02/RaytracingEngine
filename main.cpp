#include "Camera/Scene.h"
#include "LightIntensity.h"
#include "Perspective.h"
#include "sphere.h"
#include "vec3.h"
#include <vector>

int main() {
    cam::Perspective camera(
        math::vec3(0, 0, 0),        // Camera position
        math::vec3(0, 0, -1),        // Target position
        math::vec3(0, 1, 0),        // Up vector
        0.1f,                             // Near plane
        1000.0f,                           // Far plane
        90.0f                             // Field of view
    );

    cam::LightIntensity sphere_color1(1.0, 0.0, 0.0);
    cam::LightIntensity background_color(0.0, 0.0, 0.0);

    math::vec3 s1_center(0, 0, 0);
    math::sphere s1(s1_center, .8f, cam::LightIntensity(0, 1, 0));
    math::vec3 s2_center(0.75, 0.75, 0);
    math::sphere s2(s2_center, .6f, cam::LightIntensity(0, 0, 1));

    std::vector<math::primitive*> objects;
    objects.push_back(&s2);
    objects.push_back(&s1);
    
    cam::Scene scene(&camera, objects, new cam::LightIntensity(1, 0, 0));

    scene.renderScene(800, 800);

    return 0;
}
