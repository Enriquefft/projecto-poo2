#include "View.hpp"
#include "Button/Button.hpp"

constexpr float TITLE_SIZE = 50;

View::View(const std::string &title, const int &width, const int &height)
    : window(width, height, title) {}

void View::startScreen() {

  const Button BUTTON1("Beggin game");

  const rl::Font TITLE_FONT("../src/assets/fonts/pixelplay.png");
  const rl::Text TITLE(TITLE_FONT, "Labyrinth game", TITLE_SIZE);

  const rl::Vector2 WINDOW_CENTER = {window.GetSize() / 2 -
                                     TITLE.MeasureEx() / 2};

  const rl::Vector2 TITLE_POS = WINDOW_CENTER - rl::Vector2(0, 40);
  const rl::Vector2 BUTTON_POS = WINDOW_CENTER + rl::Vector2(0, 40);

  while (!window.ShouldClose()) {
    BeginDrawing();

    window.ClearBackground();

    BUTTON1.Draw(BUTTON_POS);
    TITLE.Draw(TITLE_POS);

    EndDrawing();
  }
}
