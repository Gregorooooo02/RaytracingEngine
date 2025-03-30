#include "Scene.h"
#include "LightIntensity.h"
#include "Orthographic.h"
#include "Perspective.h"
#include "primitive.h"

#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>

using namespace cam;

Scene::Scene() {
  this->camera = new Perspective();
  this->objects = std::vector<math::primitive *>();

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      this->colors[i][j] = new LightIntensity;
    }
  }
}

Scene::Scene(Camera *camera, std::vector<math::primitive *> objects,
             LightIntensity *colors[6][6]) {
  this->camera = camera;
  this->objects = objects;

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      this->colors[i][j] = colors[i][j];
    }
  }
}

Image Scene::renderScene(int width, int height) {
  int width_chunk_size = width / 5;
  int height_chunk_size = height / 5;
  Image img(width, height);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int current_chunk_x = std::floor(x / width_chunk_size);
      int current_chunk_y = std::floor(y / height_chunk_size);
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
          pixel_color = pixel_color + *this->colors[current_chunk_x][current_chunk_y];
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
