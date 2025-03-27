#include "Image.h"

#include <fstream>

using namespace cam;

Image::Image(int w, int h) : width(w), height(h) {
    pixels.resize(width * height);
}

void Image::setPixel(int x, int y, const LightIntensity& color) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }
    pixels[y * width + x] = color;
}

void Image::save(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        throw std::runtime_error("Could not open file for writing");
    }

    ofs << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const LightIntensity& color = pixels[y * width + x];
            ofs << color.red() << " " << color.green() << " " << color.blue() << "\n";
        }
        ofs << "\n";
    }

    ofs.close();
}