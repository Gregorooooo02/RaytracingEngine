#include "Scene.h"
#include "LightIntensity.h"
#include "Orthographic.h"
#include "Perspective.h"
#include "sphere.h"
#include "vec3.h"

#include <iostream>
#include <vector>

int main() {
    cam::Orthographic orto(
        math::vec3(0, 0, 0),        // Camera position
        math::vec3(0, 0, -1),       // Target position
        math::vec3(0, 1, 0),        // Up vector
        0.1f,                             // Near plane
        1000.0f                           // Far plane
    );

    cam::Perspective persp(
        math::vec3(0, 0, 0),        // Camera position
        math::vec3(0, 0, 1),        // Target position
        math::vec3(0, 1, 0),        // Up vector
        0.1f,                             // Near plane
        1000.0f,                          // Far plane
        10,                               // Number of samples
        90.0f                             // Field of view
    );

    math::vec3 s1_center(0, 0, -1);
    math::sphere s1(s1_center, .5f, cam::LightIntensity(0, 1, 0));
    math::vec3 s2_center(1, 0, -1.5f);
    math::sphere s2(s2_center, .2f, cam::LightIntensity(0, 0, 1));

    std::vector<math::primitive*> objects;
    // objects.push_back(&s2);
    objects.push_back(&s1);

    std::cout << "Choose camera type (1 for Orthographic, 2 for Perspective): ";
    int choice;
    std::cin >> choice;

    cam::Scene scene;

    if (choice == 1) {
        std::cout << "Using Orthographic camera." << std::endl;
        scene = cam::Scene(&orto, objects, new cam::LightIntensity(1, 1, 1));
    } else if (choice == 2) {
        std::cout << "Using Perspective camera." << std::endl;
        scene = cam::Scene(&persp, objects, new cam::LightIntensity(1, 1, 1));
    } else {
        std::cerr << "Invalid choice. Defaulting to Orthographic camera." << std::endl;
        scene = cam::Scene(&orto, objects, new cam::LightIntensity(1, 1, 1));
    }
    scene.renderScene(10, 10);

    return 0;
}
