#ifndef VIEW_H
#define VIEW_H

#include <raylib-cpp.hpp>
#include <string_view>

constexpr std::string_view WINDOW_TITLE = "GAME_NAME";
constexpr int VIEW_WIDTH = 800;
constexpr int VIEW_HEIGHT = 600;

class View {
public:
  explicit View(const std::string &title = WINDOW_TITLE.data(),
                const int &width = VIEW_HEIGHT,
                const int &height = VIEW_HEIGHT);

private:
  raylib::Window window;
};

#endif // !VIEW_H
