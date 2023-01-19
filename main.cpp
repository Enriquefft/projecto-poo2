#pragma GCC diagnostic push
#pragma clang diagnostic push
#pragma clang attribute push(__attribute__((no_sanitize("undefined"))),        \
                             apply_to = function)

#pragma GCC diagnostic ignored "-Weverything"
#pragma clang diagnostic ignored "-Weverything"

#include "raylib-cpp.hpp"
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#pragma clang attribute pop

#include <iostream>

struct Padded {
  int i;
  bool b;
  float f;
};

int main() {
  int screenWidth = 800;
  int screenHeight = 450;
  constexpr auto was_padded =
      sizeof(Padded) != sizeof(int) + sizeof(bool) + sizeof(float);

  raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

  int x = 3;
  SetTargetFPS(60);

  while (!window.ShouldClose()) {
    BeginDrawing();

    window.ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);

    EndDrawing();
  }

  // UnloadTexture() and CloseWindow() are called automatically.

  return 0;
}
