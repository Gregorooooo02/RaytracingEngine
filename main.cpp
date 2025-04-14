#include "DirectionalLight.h"
#include "Image.h"
#include "LightIntensity.h"
#include "Orthographic.h"
#include "Perspective.h"
#include "Scene.h"
#include "SoftPointLight.h"
#include "SpotLight.h"
#include "Utils/cursorHider.h"
#include "plane.h"
#include "sphere.h"
#include "vec3.h"
#include <AreaLight.h>
#include <cmath>
#include <cstdlib>
#include <future>
#include <iostream>
#include <string>
#include <vector>

cam::Image run(cam::Scene *scene, int *done, int width, int height) {
  cam::Image foo = scene->renderScene(width, height, done);
  return foo;
}

int main() {
  CursorHider foo;
#pragma region Camera
  cam::Orthographic orto(math::vec3(0, 0.15f, 2),  // Camera position
                         math::vec3(0, 0.15f, -1), // Target position
                         math::vec3(0, 1, 0),      // Up vector
                         0.1f,                     // Near plane
                         1000.0f,                  // Far plane
                         10                        // Number of samples
  );
  cam::Perspective persp(math::vec3(0, 0.5f, 2),  // Camera position
                         math::vec3(0, 0.5f, -1), // Target position
                         math::vec3(0, 1, 0),     // Up vector
                         0.1f,                    // Near plane
                         1000.0f,                 // Far plane
                         50,                      // Number of samples
                         90.0f                    // Field of view
  );
#pragma endregion

#pragma region Material
  Material matReflection(
      cam::LightIntensity(0.01, 0.01, 0.01), cam::LightIntensity(1.0, 1.0, 1.0),
      cam::LightIntensity(0.7, 0.7, 0.7), 50, 1.0f, 0.0f, 1.0f);
  Material matRefraction(
      cam::LightIntensity(0.01, 0.01, 0.01), cam::LightIntensity(1.0, 1.0, 1.0),
      cam::LightIntensity(0.7, 0.7, 0.7), 50, 0.0f, 1.0f, 1.7f);
  // Blue material
  Material mat2(cam::LightIntensity(0, 0, 0.01),
                cam::LightIntensity(0.0, 0.0, 1.0),
                cam::LightIntensity(0.0, 0.0, 0.0), 50, 0.0f, 0.0f, 1.0f);
  // White material
  Material mat3(cam::LightIntensity(0.01f, 0.01f, 0.01f),
                cam::LightIntensity(0.8f, 0.8f, 0.8f),
                cam::LightIntensity(0.0f, 0.0f, 0.0f), 0, 0.0f, 0.0f, 1.0f);
  // Red material
  Material mat4(cam::LightIntensity(0.01f, 0.0f, 0.0f),
                cam::LightIntensity(1.0f, 0.0f, 0.0f),
                cam::LightIntensity(0.0f, 0.0f, 0.0f), 0, 0.0f, 0.0f, 1.0f);
  // Black material
  Material mat6(cam::LightIntensity(0, 0, 0), cam::LightIntensity(0, 0, 0),
                cam::LightIntensity(0, 0, 0), 0, 0.0f, 0.0f, 1.0f);
#pragma endregion

#pragma region Lights
  licht::DirectionalLight light1(cam::LightIntensity(1, 1, 1),
                                 math::vec3(0, -1, -1));
  // Point light from the back
  licht::SoftPointLight lightPoint1(cam::LightIntensity(1, 1, 1),
                                    math::vec3(0, 1.5f, -0.25f), 1.0f, 1.0f,
                                    0.5f, 0.2f, 20);
  // Point light from the left
  licht::SoftPointLight lightPoint2(cam::LightIntensity(1, 1, 1),
                                    math::vec3(-1.25f, 1.5f, 0.5f), 1.0f, 1.0f,
                                    0.5f, 0.2f, 20);
  // Point light from the right
  licht::SoftPointLight lightPoint3(cam::LightIntensity(1, 1, 1),
                                    math::vec3(1.25f, 1.5f, 0.5f), 1.0f, 1.0f,
                                    0.5f, 0.2f, 20);
  licht::SpotLight light3(cam::LightIntensity(1, 1, 1), math::vec3(0, 2, 0.5f),
                          math::vec3(0, -1, 0), 1.0f, 0.0f, 0.0f,
                          45.0f, // Cut-off angle
                          30.0f  // Drop-off angle
  );
  // Area light from the top
  licht::AreaLight light4(cam::LightIntensity(1, 1, 1),
                          math::vec3(0, 2, 0.5),  // Center of the area light
                          math::vec3(0.5f, 0, 0), // U direction
                          math::vec3(0, 0, 0.5f), // V direction
                          5, // Number of samples in U direction
                          5  // Number of samples in V direction
  );
#pragma endregion

#pragma region Objects
  math::vec3 s1Center(-0.5f, 0, 0);
  math::sphere s1(s1Center, 0.5f, matReflection);
  math::vec3 s2Center(0.25f, -0.1f, 0.5f);
  math::sphere s2(s2Center, 0.4f, matRefraction);

  // Plane creating a floor
  math::vec3 p1Normal(0, 1, 0);    // Normal pointing up
  math::vec3 p1Center(0, -0.5, 0); // Center of the plane
  math::plane p1(p1Normal, p1Center, mat3);

  // Plane creating a wall on the left side
  math::vec3 p2Normal(1, 0, 0);     // Normal pointing right
  math::vec3 p2Center(-1.5f, 0, 0); // Center of the plane
  math::plane p2(p2Normal, p2Center, mat4);

  // Plane creating a wall on the right side
  math::vec3 p3Normal(-1, 0, 0);   // Normal pointing left
  math::vec3 p3Center(1.5f, 0, 0); // Center of the plane
  math::plane p3(p3Normal, p3Center, mat2);

  // Plane creating a wall on the back side
  math::vec3 p4Normal(0, 0, 1);  // Normal pointing back
  math::vec3 p4Center(0, 0, -1); // Center of the plane
  math::plane p4(p4Normal, p4Center, mat3);

  // Plane creating a wall on top
  math::vec3 p5Normal(0, -1, 0);    // Normal pointing down
  math::vec3 p5Center(0, 2.75f, 0); // Center of the plane
  math::plane p5(p5Normal, p5Center, mat6);
#pragma endregion

  std::vector<licht::Light *> lights;
  lights.push_back(&lightPoint1);
  lights.push_back(&lightPoint2);
  lights.push_back(&lightPoint3);

  std::vector<math::primitive *> objects;
  objects.push_back(&s1);
  objects.push_back(&s2);

  objects.push_back(&p1);
  objects.push_back(&p2);
  objects.push_back(&p3);
  objects.push_back(&p4);
  objects.push_back(&p5);

  std::cout << "Choose camera type (1 for Orthographic, 2 for Perspective): ";
  int choice;
  std::cin >> choice;

  cam::Scene scene;

  cam::LightIntensity bg(0, 0, 0);

  if (choice == 1) {
    std::cout << "Using Orthographic camera." << std::endl;
    scene = cam::Scene(&orto, lights, objects, bg, 1);
  } else if (choice == 2) {
    std::cout << "Using Perspective camera." << std::endl;
    scene = cam::Scene(&persp, lights, objects, bg, 10);
  } else {
    std::cerr << "Invalid choice. Defaulting to Orthographic camera."
              << std::endl;
    scene = cam::Scene(&orto, lights, objects, bg, 4);
  }

  int done = 0;
  int width = 100;
  int height = 100;
  int total = width * height;
  auto thread = std::async(run, &scene, &done, width, height);

  std::cout << "\033[2J\033[1;1H";

  while (done < total) {
    float ratio = (float)done / (float)total * 40;
    int doneSegments = std::round(ratio);
    std::string progress = "|";
    for (int i = 0; i < doneSegments; i++) {
      progress += "=";
    }

    for (int i = 0; i < 40 - doneSegments; i++) {
      progress += "-";
    }

    progress += "|";

    std::cout << "\033[2F";

    std::cout << "Rendering progress: "
              << std::round((float(done) / total) * 10000) / 100 << "%\n"
              << progress << "\n";
  }

  cam::Image image = thread.get();

  cam::Camera *cam = scene.camera;
  if (dynamic_cast<cam::Perspective *>(cam)) {
    image.save("perspective.ppm");
    std::cout << "Image saved as perspective.ppm" << std::endl;
  } else if (dynamic_cast<cam::Orthographic *>(cam)) {
    image.save("orthographic.ppm");
    std::cout << "Image saved as orthographic.ppm" << std::endl;
  } else {
    std::cout << "Unknown camera type." << std::endl;
  }

  return 0;
}
