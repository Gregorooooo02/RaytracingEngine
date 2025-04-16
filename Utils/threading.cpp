#include "Scene.h"
#include <cmath>
#include <iostream>
#include <queue>
#include <thread>
#include <threading.h>

ThreadManager::ThreadManager(int width, int height, int threadCount) {
  this->threadCount = threadCount;
  this->widht = width;
  this->height = height;
  this->pixels = std::queue<Pixels>();

  int widthChunk = width / threadCount;
  int widthReminder = width % threadCount;
  int heightChunk = height / threadCount;
  int heightReminder = height % threadCount;
  int currentWidth = 0;
  int currentHeight = 0;

  for (int i = 0; i < threadCount; i++) {
    Pixels pixel;
    for (int j = 0; j < threadCount; j++) {
      pixel = Pixels();
      pixel.width = width;
      pixel.height = height;
      pixel.startWidth = currentWidth;
      pixel.endWidth = currentWidth + widthChunk;
      pixel.startHeight = currentHeight;
      pixel.endHeight = currentHeight + heightChunk;

      if (j < widthReminder) {
        pixel.endWidth++;
      }

      currentWidth = pixel.endWidth;

      this->pixels.push(pixel);
    }

    if (i < heightReminder) {
      pixel.endHeight++;
    }

    currentHeight = pixel.endHeight;
    currentWidth = 0;
  }
}

void ThreadManager::run(cam::Scene *scene, cam::Image *image,
                        std::atomic<int> &done,
                        std::vector<std::thread> *threads) {
  for (int i = 0; i < this->threadCount; i++) {
    std::thread thread = std::thread([&] {
      while (true) {
        this->mutex.lock();
        if (!this->pixels.empty()) {
          Pixels pixel = this->pixels.front();
          this->pixels.pop();
          this->mutex.unlock();
          scene->renderScene(pixel.width, pixel.height, pixel.startWidth,
                             pixel.endWidth, pixel.startHeight, pixel.endHeight,
                             done, image);
        } else {
          this->mutex.unlock();
          break;
        }
      }
    });
    threads->push_back(std::move(thread));
  }

  while (!this->pixels.empty()) {
  }
}

ThreadManager::~ThreadManager() {}
