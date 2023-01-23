#ifndef VIEW_H
#define VIEW_H

#include <raylib-cpp.hpp>

class View {
public:
  View(const std::string &title, const int &width, const int &height);

private:
  raylib::Window window;
};

#endif // !VIEW_H
