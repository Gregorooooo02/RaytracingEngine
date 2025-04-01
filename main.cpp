#include "Scene.h"
#include "LightIntensity.h"
#include "Orthographic.h"
#include "Perspective.h"
#include "sphere.h"
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
        100                               // Number of samples
    );

    cam::Perspective persp(
        math::vec3(0, 0, 0),        // Camera position
        math::vec3(0, 0, -1),       // Target position
        math::vec3(0, 1, 0),        // Up vector
        0.1f,                             // Near plane
        1000.0f,                          // Far plane
        100,                              // Number of samples
        90.0f                             // Field of view
    );

    math::vec3 s1_center(0, 0, -1);
    math::sphere s1(s1_center, .5f, cam::LightIntensity(0, 0, 1));
    math::vec3 s2_center(0.5, 0, -1);
    math::sphere s2(s2_center, .25f, cam::LightIntensity(1, 0, 0));

    math::vec3 s3_center(0, -100, -1);
    math::sphere s3(s3_center, 100, cam::LightIntensity(1, 1, 0));

    std::vector<math::primitive*> objects;
    objects.push_back(&s1);
    objects.push_back(&s2);
    //objects.push_back(&s3);

    std::cout << "Choose camera type (1 for Orthographic, 2 for Perspective): ";
    int choice;
    std::cin >> choice;

    cam::Scene scene;

    cam::LightIntensity* colors[6][6];

    srand(time(0));

    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
        colors[i][j] = new cam::LightIntensity(
            (float)rand() / RAND_MAX,
            (float)rand() / RAND_MAX,
            (float)rand() / RAND_MAX
            );
      } 
    }

    if (choice == 1) {
        std::cout << "Using Orthographic camera." << std::endl;
        scene = cam::Scene(&orto, objects, colors);
    } else if (choice == 2) {
        std::cout << "Using Perspective camera." << std::endl;
        scene = cam::Scene(&persp, objects, colors);
    } else {
        std::cerr << "Invalid choice. Defaulting to Orthographic camera." << std::endl;
        scene = cam::Scene(&orto, objects, colors);
    }
    scene.renderScene(300, 300);

    return 0;
}
