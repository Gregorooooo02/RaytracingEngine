#include "Image.h"
#include "LightIntensity.h"
#include "Orthographic.h"
#include "Perspective.h"

#include "sphere.h"
#include "vec3.h"

#include <iostream>

int main() {
    int img_width = 1200;
    int img_height = 800;

    cam::Perspective camera(
        math::vec3(0, 0, 0),        // Camera position
        math::vec3(0, 0, -1),        // Target position
        math::vec3(0, 1, 0),        // Up vector
        0.1f,                             // Near plane
        1000.0f,                           // Far plane
        90.0f                             // Field of view
    );

    cam::LightIntensity sphere_color1(1.0, 0.0, 0.0);
    cam::LightIntensity background_color(0.0, 0.0, 0.0);

    float R = M_PI / 4;
    math::vec3 sphere_center(0, 0, -2);
    math::sphere sphere(sphere_center, R);

    cam::Image img(img_width, img_height);

    for (int y = 0; y < img_height; y++) {
        for (int x = 0; x < img_width; x++) {
            math::ray ray = camera.generateRay(x, y, img_width, img_height);
            if (sphere.hit(ray, 0.0f, 1000.0f)) {
                img.setPixel(x, y, sphere_color1);
            } else {
                img.setPixel(x, y, background_color);
            }
        }
    }

    img.save("output.ppm");

    std::cout << "Image saved as output.ppm" << std::endl;
    return 0;
}
