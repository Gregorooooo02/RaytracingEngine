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
    std::vector<math::vec3> normals;
    std::vector<math::triangle> faces;

    bool loadObject(const std::string& path, Material &material) {
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
                vertices.emplace_back(x, y, z);
            } else if (type == "vn") {
                float nx, ny, nz;
                iss >> nx >> ny >> nz;
                normals.emplace_back(nx, ny, nz);
            } else if (type == "f") {
                std::string s1, s2, s3;
                iss >> s1 >> s2 >> s3;

                int vIdx[3], nIdx[3];
                parseFaceToken(s1, vIdx[0], nIdx[0]);
                parseFaceToken(s2, vIdx[1], nIdx[1]);
                parseFaceToken(s3, vIdx[2], nIdx[2]);

                math::vec3 v0 = vertices[vIdx[0] - 1];
                math::vec3 v1 = vertices[vIdx[1] - 1];
                math::vec3 v2 = vertices[vIdx[2] - 1];

                math::vec3 n0 = (nIdx[0] > 0 ? normals[nIdx[0] - 1] : math::vec3(0, 1, 0));
                math::vec3 n1 = (nIdx[1] > 0 ? normals[nIdx[1] - 1] : math::vec3(0, 1, 0));
                math::vec3 n2 = (nIdx[2] > 0 ? normals[nIdx[2] - 1] : math::vec3(0, 1, 0));

                faces.emplace_back(v0, v1, v2, n0, n1, n2, material);
            }
        }
        return true;
    }

private:
    void parseFaceToken(const std::string &token, int &vIdx, int &nIdx) {
        vIdx = nIdx = -1;
        std::stringstream ss(token);
        std::string part;
        std::vector<std::string> parts;

        while (std::getline(ss, part, '/')) {
            parts.push_back(part);
        }

        if (parts.size() == 1) {
            vIdx = std::stoi(parts[0]);
        } else if (parts.size() == 2) {
            vIdx = std::stoi(parts[0]);
            nIdx = std::stoi(parts[1]);
        } else if (parts.size() == 3) {
            vIdx = std::stoi(parts[0]);
            if (!parts[2].empty()) {
                nIdx = std::stoi(parts[2]);
            }
        }
    }
};