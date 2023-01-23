#include "View.hpp"
#include <iostream>

View::View(const std::string &title, const int &width, const int &height)
    : window(width, height, title) {}
