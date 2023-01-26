#include "View.hpp"
#include "Button/Button.hpp"

View::View(const std::string &title, const int &width, const int &height)
    : window(width, height, title) {}

void View::startScreen() {

  Button button1("Button1");
  Button button2("another button");

  while (!window.ShouldClose()) {
    BeginDrawing();

    window.ClearBackground(RAYWHITE);

    const char *dir = GetApplicationDirectory();
    // DrawText("Congrats! You created your first window!", 190, 200, 20,
    // LIGHTGRAY);
    // DrawText(dir, 40, 40, 20, LIGHTGRAY);

    button1.Draw(100, 100);
    button2.Draw(300, 300);
    button1.Draw(250, 500);

    // Object methods.
    // logo.Draw(screenWidth / 2 - logo.GetWidth() / 2,
    //           screenHeight / 2 - logo.GetHeight() / 2);

    EndDrawing();
  }
}
