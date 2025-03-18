#include "Window.h"

bool Window::init(unsigned int width, unsigned int height, const std::string& title) {
    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return false;
    }

    return true;
}

void Window::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        /* Poll events in a loop */
        glfwPollEvents();
    }
}

void Window::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}