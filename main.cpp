#include <memory>

#include "Window.h"

int main() {
    std::unique_ptr<Window> window = std::make_unique<Window>();

    if (!window -> init(800, 600, "Hello World!")) {
        return -1;
    }

    window -> mainLoop();
    window -> cleanup();

    return 0;
}