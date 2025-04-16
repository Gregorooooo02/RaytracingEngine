#pragma once
#include "Image.h"
#include "Scene.h"
#include <mutex>
#include <queue>
#include <thread>

struct Pixels {
  int width;
  int height;
  int startWidth;
  int endWidth;
  int startHeight;
  int endHeight;
};

class ThreadManager {
private:
  std::mutex mutex;
  int threadCount;
  int widht;
  int height;

public:
  std::queue<Pixels> pixels;
  ThreadManager(int width, int height, int threadCount);
  ~ThreadManager();
  void run(cam::Scene *scene, cam::Image *image,
           std::atomic<int> &done, std::vector<std::thread> *threads);
};
