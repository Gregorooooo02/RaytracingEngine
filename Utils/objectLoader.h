#pragma once

#include "vec3.h"
#include "triangle.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class ObjectLoader {
    public:
        std::vector<math::vec3> vertices;
        std::vector<math::triangle> faces;

        inline bool loadObject(const std::string& path) {
            std::ifstream file(path);
            if (!file.is_open()) {
                std::cerr << "Could not open file " << path << std::endl;
                return false;
            }
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string type;
                iss >> type;    
                if (type == "v") {
                    float x, y, z;
                    iss >> x >> y >> z;
                    math::vec3 vertex(x, y, z);
                    vertices.push_back(vertex);
                } else if (type == "f") {
                    int v1, v2, v3;
                    iss >> v1 >> v2 >> v3;
                    // Subtracting 1 because obj files are 1-indexed
                    faces.push_back(math::triangle(vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1]));
                }
            }
            return true;
        }
};