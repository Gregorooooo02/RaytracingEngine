#include "objectLoader.h"

#include <iostream>

int main() {
  std::cout << "Hello world!" << std::endl;

  ObjectLoader loader;
  loader.loadObject("../Assets/cube.obj");

  for (int i = 0; i < loader.vertices.size(); i++) {
    std::cout << "Vertex " << i << ": " << loader.vertices[i].x << " " << loader.vertices[i].y << " " << loader.vertices[i].z << std::endl;
  }
  
  for (int i = 0; i < loader.faces.size(); i++) {
    std::cout << "Face " << i << ": " << std::endl;
    for (int j = 0; j < 3; j++) {
      std::cout << "Vertex " << j << ": " << loader.faces[i].vertices[j].x << " " << loader.faces[i].vertices[j].y << " " << loader.faces[i].vertices[j].z << std::endl;
    }
  }

  return 0;
}
