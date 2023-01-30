#include <iostream>
#include <memory>
#include <raylib-cpp.hpp>
#include <raylib.h>

namespace rl = raylib;
constexpr std::string_view DEFAULT_TEXTURE_PATH =
    "../src/assets/Textures/test_old_button.png";

class Button { // NOLINT
public:
  Button() {

    if (!shared_texture) {
      shared_texture =
          std::make_unique<rl::Texture>(DEFAULT_TEXTURE_PATH.data());
    }
  }

  void Draw(const int &posX, const int &posY) const {
    shared_texture->Draw(posX, posY);
  }

private:
  inline static std::unique_ptr<rl::Texture> shared_texture = nullptr;

  [[nodiscard]] static const rl::Texture &texture() { return *shared_texture; }
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
