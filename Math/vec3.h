#pragma once

class Vec3 {
public:
  float x, y, z;
  Vec3();
  Vec3(float x, float y, float z);
  Vec3(Vec3 &vec);
  ~Vec3();
  void add(Vec3 &vec);
  void substract(Vec3 &vec);
  void multiply(float multiplier);
  void divide(float divider);
  float len();
  void normalize();
  float dot_product(Vec3 &vec);
  Vec3 cross_product(Vec3 &vec);
};
