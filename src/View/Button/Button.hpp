#ifndef BUTTON_H
#define BUTTON_H

#include <raylib-cpp.hpp>
#include <string_view>
#include <vector>

constexpr std::string_view DEFAULT_FONT_PATH =
    "../src/assets/fonts/alpha_beta.png";
constexpr std::string_view DEFAULT_TEXTURE_PATH =
    "../src/assets/Textures/test_old_button.png";
constexpr int DEFAULT_FONT_SIZE = 20;
constexpr int DEFAULT_MAX_TEXT = 50;

namespace rl = raylib;

class Button {
public:
  Button() = delete;
  explicit Button(std::string_view text,
                  rl::Texture &customTexture = defaultTexture(),
                  float fontSize = DEFAULT_FONT_SIZE,
                  const rl::Color &color = WHITE);
  // explicit Button(std::string_view text, rl::Font &customFont =
  // defaultFont());

  [[nodiscard]] bool isClicked(const int &posX, const int &posY) const;

  void draw(const int &posX = 0, const int &posY = 0) const;

  [[nodiscard]] inline bool isClicked(const rl::Vector2 &pos) const {
    return isClicked(static_cast<int>(pos.x), static_cast<int>(pos.y));
  }

  inline void Draw(const rl::Vector2 &pos) const {
    this->draw(static_cast<int>(pos.x), static_cast<int>(pos.y));
  }

  [[nodiscard]] inline rl::Vector2 GetSize() const {
    return m_texture.GetSize();
  }

private:
  rl::Text m_text;
  rl::Texture &m_texture;

  static rl::Font &defaultFont();
  static rl::Texture &defaultTexture();
};

#endif // !BUTTON_H
