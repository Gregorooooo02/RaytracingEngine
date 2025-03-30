#include "Scene.h"
#include "LightIntensity.h"
#include "Orthographic.h"
#include "Perspective.h"
#include "primitive.h"

#include <iostream>
#include <ostream>
#include <vector>

using namespace cam;

Scene::Scene() {
  this->camera = new Perspective();
  this->backgroundColor = new LightIntensity(1, 0, 0);
  this->objects = std::vector<math::primitive *>();
}

Scene::Scene(Camera *camera, std::vector<math::primitive *> objects,
             LightIntensity *backgroundColor) {
  this->camera = camera;
  this->backgroundColor = backgroundColor;
  this->objects = objects;
}

Image Scene::renderScene(int width, int height) {
  Image img(width, height);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      LightIntensity pixel_color;
      for (int samples = 0; samples < camera->samplesCount; samples++) {
        bool hit = false;
        math::ray ray = camera->generateRay(x, y, width, height);
        for (int o = 0; o < this->objects.size(); o++) {
          if (this->objects[o]->hit(ray)) {
            pixel_color = pixel_color + this->objects[o]->color;
            hit = true;
            break;
          }
        }
        if (!hit) {
          pixel_color = pixel_color + *this->backgroundColor;
        }
      }
      pixel_color = pixel_color / camera->samplesCount;
      img.setPixel(x, y, pixel_color);
    }
  }

  Camera *cam = this->camera;
  if (dynamic_cast<Perspective *>(cam)) {
    img.save("perspective.ppm");
    std::cout << "Image saved as perspective.ppm" << std::endl;
  } else if (dynamic_cast<Orthographic *>(cam)) {
    img.save("orthographic.ppm");
    std::cout << "Image saved as orthographic.ppm" << std::endl;
  } else {
    std::cout << "Unknown camera type." << std::endl;
  }

  return img;
}
