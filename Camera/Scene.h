#pragma once
#include "Camera.h"
#include "Image.h"
#include "LightIntensity.h"
#include "Light.h"
#include "primitive.h"

#include <atomic>
#include <vector>

namespace cam {
  enum RenderMode {
    RAY_TRACING,
    PATH_TRACING
  };
  class Scene {
    private:
      RenderMode mode = RAY_TRACING;
      std::vector<licht::Light*> lights;
      std::vector<math::primitive*> objects;

      LightIntensity bg;
      LightIntensity* colors[6][6];
      int maxDepth = 5;
    public:
      Camera* camera;
      Scene();
      Scene(Camera* camera, std::vector<licht::Light*> lights, std::vector<math::primitive*> objects, LightIntensity* colors[6][6], int maxDepth, RenderMode mode = RAY_TRACING);
      Scene(Camera* camera, std::vector<licht::Light*> lights, std::vector<math::primitive*> objects, LightIntensity bg, int maxDepth, RenderMode mode = RAY_TRACING);
      ~Scene() = default;
      void renderScene(int width, int height, int startWidth, int endWidth, int startHeight, int endHeight, std::atomic<int> &done, Image *image);
  };
}
