#include "objectLoader.h"

#include <iostream>

int main() {
  std::cout << "Hello world!" << std::endl;

  ObjectLoader loader;
  loader.loadObject("../Assets/cube.obj");

  std::cout << "Vertices: " << loader.vertices.size() << std::endl;
  std::cout << "Faces: " << loader.faces.size() << std::endl;

  return 0;
}
