#include "Scene.h"
#include "LightIntensity.h"
#include "Perspective.h"
#include "Orthographic.h"
#include "primitive.h"

#include <iostream>
#include <ostream>
#include <vector>

using namespace cam;

Scene::Scene() {
  this->camera = new Perspective();
  this->backgroundColor = new LightIntensity();
  this->objects = std::vector<math::primitive *>();
}

Scene::Scene(Camera *camera, std::vector<math::primitive *> objects,
             LightIntensity *backgroundColor) {
  this->camera = camera;
  this->backgroundColor = backgroundColor;
  this->objects = objects;
}

Image Scene::renderScene(int width, int height) {
  cam::Image img(width, height);
  for (int y = 0; y < width; y++) {
    for (int x = 0; x < height; x++) {
      math::ray ray = camera->generateRay(x, y, width, height);
      bool hit = false;
      for (int o = 0; o < this->objects.size(); o++) {
        if (this->objects[o]->hit(ray)) {
          img.setPixel(x, y, this->objects[o]->color);
          hit = true;
        }
      }
      if (!hit) {
        img.setPixel(x, y, *this->backgroundColor);
      }
    }
  }

  Camera* cam = this->camera;
  if (dynamic_cast<Perspective*>(cam)) {
    img.save("perspective.ppm");
    std::cout << "Image saved as perspective.ppm" << std::endl;
  }
  else if (dynamic_cast<Orthographic*>(cam)) {
    img.save("orthographic.ppm");
    std::cout << "Image saved as orthographic.ppm" << std::endl;
  }
  else {
    std::cout << "Unknown camera type." << std::endl;
  }

  return img;
}
