#pragma once
#include "Camera.h"
#include "Image.h"
#include "LightIntensity.h"
#include "Light.h"
#include "primitive.h"

#include <vector>

namespace cam {
  class Scene {
    private:
      Camera* camera;

      std::vector<licht::Light*> lights;
      std::vector<math::primitive*> objects;

      LightIntensity bg;
      LightIntensity* colors[6][6];
    public:
      Scene();
      Scene(Camera* camera, std::vector<licht::Light*> lights, std::vector<math::primitive*> objects, LightIntensity* colors[6][6]);
      Scene(Camera* camera, std::vector<licht::Light*> lights, std::vector<math::primitive*> objects, LightIntensity bg);
      ~Scene() = default;
      Image renderScene(int width, int height);
  };
}
