#include "View.hpp"
#include "Button/Button.hpp"

constexpr float TITLE_SIZE = 50;

View::View(const std::string &title, const int &width, const int &height)
    : window(width, height, title) {}

void View::startScreen() {

  Button button1("Beggin game");

  rl::Font title_font("../src/assets/fonts/pixelplay.png");
  rl::Text title(title_font, "Labyrinth game", TITLE_SIZE);

  rl::Vector2 window_center = {window.GetSize() / 2 - title.MeasureEx() / 2};
  const rl::Vector2 TITLE_POS = window_center - rl::Vector2(0, 40);
  const rl::Vector2 BUTTON_POS = window_center + rl::Vector2(0, 40);

  while (!window.ShouldClose()) {
    BeginDrawing();

    window.ClearBackground();

    button1.Draw(BUTTON_POS);

    title.Draw(TITLE_POS);

    EndDrawing();
  }
}
