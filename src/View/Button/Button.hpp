#ifndef BUTTON_H
#define BUTTON_H

#include <Color.hpp>
#include <Texture.hpp>
#include <raylib-cpp.hpp>
#include <string_view>
#include <vector>

constexpr std::string_view DEFAULT_FONT_PATH = "../../assets/fonts/FONT.TTF";
constexpr std::string_view DEFAULT_TEXTURE_PATH =
    "../../assets/textures/TEXTURE.jpg";
constexpr float DEFAULT_FONT_SIZE = 20;
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

private:
  rl::Text m_text;
  rl::Texture &m_texture;

  static rl::Font &defaultFont();
  static rl::Texture &defaultTexture();
};

#endif // !BUTTON_H
