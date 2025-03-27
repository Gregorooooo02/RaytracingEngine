#pragma once
#include "LightIntensity.h"
#include <vector>

namespace cam {
    class Image {
        private:
          int width;
          int height;
          std::vector<LightIntensity> pixels;

        public:
          Image(int w, int h);

          void setPixel(int x, int y, const LightIntensity& color);
          void save(const std::string& filename) const;
    };
} // namespace cam
