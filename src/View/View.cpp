#include "View.hpp"
#include <iostream>

View::View(const std::string &title, const int &width, const int &height)
    : window(width, height, title) {}

void View::startScreen() {

  while (!window.ShouldClose()) {
    BeginDrawing();

    window.ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);

    // Object methods.
    // logo.Draw(screenWidth / 2 - logo.GetWidth() / 2,
    //           screenHeight / 2 - logo.GetHeight() / 2);

    EndDrawing();
  }
}
