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

  int widthChunk = width / (threadCount * 2);
  int widthReminder = width % (threadCount * 2);
  int heightChunk = height / (threadCount * 2);
  int heightReminder = height % (threadCount * 2);
  int currentWidth = 0;
  int currentHeight = 0;

  for (int i = 0; i < (threadCount * 2); i++) {
    Pixels pixel;
    for (int j = 0; j < (threadCount * 2); j++) {
      pixel.width = width;
      pixel.height = height;
      pixel.startWidth = currentWidth;
      pixel.endWidth = currentWidth + widthChunk;
      pixel.startHeight = currentHeight;
      pixel.endHeight = currentHeight + heightChunk;

      currentWidth = pixel.endWidth;

      this->pixels.push(pixel);
    }

    if (widthReminder > 0) {
      pixel.width = width;
      pixel.height = height;
      pixel.startWidth = width - widthReminder;
      pixel.endWidth = width;
      pixel.startHeight = currentHeight;
      pixel.endHeight = currentHeight + heightChunk;

      this->pixels.push(pixel);
    }

    currentHeight = pixel.endHeight;
    currentWidth = 0;
  }

  if (heightReminder > 0) {
    Pixels pixel;
    for (int i = 0; i < threadCount * 2; i++) {
      pixel.width = width;
      pixel.height = height;
      pixel.startWidth = currentWidth;
      pixel.endWidth = currentWidth + widthChunk;
      pixel.startHeight = height - heightReminder;
      pixel.endHeight = height;

      this->pixels.push(pixel);
      currentWidth = pixel.endWidth;
    }

    pixel.width = width;
    pixel.height = height;
    pixel.startWidth = width - widthReminder;
    pixel.endWidth = width;
    pixel.startHeight = height - heightReminder;
    pixel.endHeight = height;

    this->pixels.push(pixel);
  }

//  while (!this->pixels.empty()) {
//    Pixels pixel = this->pixels.front();
//    this->pixels.pop();
//    std::cout << pixel.startWidth << ":" << pixel.endWidth << " "
//              << pixel.startHeight << ":" << pixel.endHeight << "\n";
//  }
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

  for (int i = 0; i < threads->size(); i++) {
    threads->at(i).join();
  }
}

ThreadManager::~ThreadManager() {}
