#pragma once

#include <iostream>
class CursorHider {
  public:
    CursorHider() {
      std::cout << "\033[?25l";
    }
    ~CursorHider() {
      std::cout << "\033[?25h";
    }
};
