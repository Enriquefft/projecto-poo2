#ifndef BUTTON_H
#define BUTTON_H

#include <Color.hpp>
#include <Texture.hpp>
#include <Vector2.hpp>
#include <raylib-cpp.hpp>
#include <raylib.h>
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
  inline void draw(int posX = 0, int posY = 0) const {

    auto text_size = m_text.MeasureEx();
    auto button_size = m_texture.GetSize();

    auto [text_x, text_y] = std::pair{posX + (static_cast<int>(button_size.x) -
                                              static_cast<int>(text_size.x)) /
                                                 2,
                                      posY + (static_cast<int>(button_size.y) -
                                              static_cast<int>(text_size.y)) /
                                                 2};

    m_texture.Draw(posX, posY);
    m_text.Draw(text_x, text_y);
  }
  inline void Draw(rl::Vector2 pos) const {
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
