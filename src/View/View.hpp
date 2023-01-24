#ifndef VIEW_H
#define VIEW_H

#include <raylib-cpp.hpp>

constexpr std::string WINDOW_TITLE = "GAME_NAME";
constexpr int VIEW_WIDTH = 800;
constexpr int VIEW_HEIGHT = 600;

class View {
public:
  explicit View(const std::string &title = WINDOW_TITLE,
                const int &width = VIEW_HEIGHT,
                const int &height = VIEW_HEIGHT);
  void startScreen();

private:
  raylib::Window window;
};

#endif // !VIEW_H
