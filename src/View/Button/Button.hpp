#ifndef BUTTON_H
#define BUTTON_H

#include <Color.hpp>
#include <Texture.hpp>
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
  inline void Draw(int posX = 0, int posY = 0) const {
    m_texture.Draw(posX, posY);

    rl::Vector2 text_pos = {static_cast<float>(posX + m_texture.GetWidth() / 2 -
                                               m_text.GetFontSize() / 2),
                            static_cast<float>(posY +
                                               m_texture.GetHeight() / 2 -
                                               m_text.GetFontSize() / 2)};
    m_text.Draw(text_pos);
  }

private:
  rl::Text m_text;
  rl::Texture &m_texture;

  static rl::Font &defaultFont();
  static rl::Texture &defaultTexture();
};

#endif // !BUTTON_H
