#include "Scene.h"
#include "DirectionalLight.h"
#include "LightIntensity.h"
#include "Orthographic.h"
#include "Perspective.h"
#include "sphere.h"
#include "plane.h"
#include "vec3.h"

#include <cstdlib>
#include <iostream>
#include <vector>

int main() {
    cam::Orthographic orto(
        math::vec3(0, 0, 0),        // Camera position
        math::vec3(0, 0, -1),       // Target position
        math::vec3(0, 1, 0),        // Up vector
        0.1f,                             // Near plane
        1000.0f,                          // Far plane
        10                               // Number of samples
    );

    cam::Perspective persp(
        math::vec3(0, 0, 0),        // Camera position
        math::vec3(0, 0, -1),       // Target position
        math::vec3(0, 1, 0),        // Up vector
        0.1f,                             // Near plane
        1000.0f,                          // Far plane
        10,                              // Number of samples
        90.0f                             // Field of view
    );

    Material mat1(
        cam::LightIntensity(0.1, 0, 0),
        cam::LightIntensity(1.0, 0.0, 0.0),
        cam::LightIntensity(0.5, 0.5, 0.5),
        50,
        0.0
    );

    licht::DirectionalLight light1(
        cam::LightIntensity(1, 1, 1),
        math::vec3(0, 1, 1)
    );

    math::vec3 s1_center(0, 0, -1);
    math::sphere s1(s1_center, .5f, mat1);

    std::vector<licht::Light*> lights;
    lights.push_back(&light1);

    std::vector<math::primitive*> objects;
    objects.push_back(&s1);

    std::cout << "Choose camera type (1 for Orthographic, 2 for Perspective): ";
    int choice;
    std::cin >> choice;

    cam::Scene scene;

    cam::LightIntensity bg(0, 0, 0);

    if (choice == 1) {
        std::cout << "Using Orthographic camera." << std::endl;
        scene = cam::Scene(&orto, lights, objects, bg);
    } else if (choice == 2) {
        std::cout << "Using Perspective camera." << std::endl;
        scene = cam::Scene(&persp, lights, objects, bg);
    } else {
        std::cerr << "Invalid choice. Defaulting to Orthographic camera." << std::endl;
        scene = cam::Scene(&orto, lights, objects, bg);
    }
    scene.renderScene(300, 300);

    return 0;
}
