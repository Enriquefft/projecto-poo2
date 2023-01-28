#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>

namespace rl = raylib;
constexpr std::string_view DEFAULT_TEXTURE_PATH =
    "../src/assets/Textures/test_old_button.png";

class Button { // NOLINT
public:
  Button() : m_texture(defaultTexture()) {}

  void Draw(const int &posX, const int &posY) const {
    m_texture.Draw(posX, posY);
  }
  // ~Button() { UnloadTexture(m_texture); }

private:
  rl::Texture &m_texture;

  static rl::Texture &defaultTexture() {
    // [[clang::no_destroy]] static rl::Texture default_texture(
    //     DEFAULT_TEXTURE_PATH.data());
    static rl::Texture default_texture(DEFAULT_TEXTURE_PATH.data());
    return default_texture;
  }
};

int main() {

  rl::Window window(800, 600, "Hello World");
  Button but;

  auto counter = 500;

  while (!window.ShouldClose()) {
    BeginDrawing();

    but.Draw(100, 100);

    std::cout << "Counter: " << counter << std::endl;
    if (--counter <= 0) {
      break;
    }

    EndDrawing();
  }

  return 0;
}
