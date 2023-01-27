#include <raylib-cpp.hpp>

constexpr std::string_view DEFAULT_TEXTURE_PATH =
    "../src/assets/Textures/test_old_button.png";

class Button {

  static raylib::Texture &defaultTexture() {
    static raylib::Texture default_texture(DEFAULT_TEXTURE_PATH.data());
    return default_texture;
  }
};

int main() {

  while (!window.ShouldClose()) {
    BeginDrawing();
  }

  EndDrawing();

  return 0;
}
