#pragma once
#include <GLFW/glfw3.h>
#include <string>

class Window {
    public:
        bool init(unsigned int width, unsigned int height, const std::string& title);
        void mainLoop();
        void cleanup();
    private:
        GLFWwindow *window = nullptr;
};
