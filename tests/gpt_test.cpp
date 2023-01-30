#include <memory>
#include <raylib-cpp.hpp>

constexpr std::string_view DEFAULT_TEXTURE_PATH =
    "../src/assets/Textures/test_old_button.png";

namespace rl = raylib;
class MyClass {
public:
  MyClass() {
    if (!sharedTexture_) {
      sharedTexture_ = std::make_unique<rl::Texture>(
          LoadTexture(DEFAULT_TEXTURE_PATH.data()));
    }
  }

  const rl::Texture &texture() const { return *sharedTexture_; }

private:
  static std::unique_ptr<rl::Texture> sharedTexture_;
};

std::unique_ptr<rl::Texture> MyClass::sharedTexture_ = nullptr;

// int main() {
//   MyClass my_class1;
//   MyClass my_class2;

//   // Both instances of the class will use the same texture
//   const Texture2D &texture1 = my_class1.texture();
//   const Texture2D &texture2 = my_class2.texture();

//   // Use the textures in your raylib code
//   DrawTexture(texture1, 0, 0, WHITE);
//   DrawTexture(texture2, 100, 100, WHITE);

//   return 0;
// }

int main() {

  rl::Window window(800, 600, "Hello World");
  MyClass but;

  auto counter = 500;

  while (!window.ShouldClose()) {
    BeginDrawing();

    but.texture().Draw(100, 100);

    std::cout << "Counter: " << counter << std::endl;
    if (--counter <= 0) {
      break;
    }

    EndDrawing();
  }

  return 0;
}
