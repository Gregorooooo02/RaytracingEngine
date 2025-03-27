#pragma once
#include "Camera.h"
#include "Image.h"
#include "LightIntensity.h"
#include "primitive.h"
#include <vector>

namespace cam {
  class Scene {
    private:
      Camera* camera; 
      std::vector<math::primitive> objects;
      LightIntensity backgroundColor;
    public:
      Scene();
      Scene(Camera* camera, std::vector<math::primitive> objects, LightIntensity backgroundColor);
      ~Scene();
      Image renderScene(int width, int height);
  };
}
