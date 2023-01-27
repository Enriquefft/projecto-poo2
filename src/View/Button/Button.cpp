#include "Button.hpp"
#include <Vector2.hpp>

// Temporal
#include <iostream>

const float TEXT_BUTTON_RATIO = 0.8F;

Button::Button(std::string_view text, rl::Texture &customTexture,
               float fontSize, const rl::Color &color)
    : m_text(rl::Text(text.data(), fontSize, color)), m_texture(customTexture) {

  raylib::Vector2 text_size = m_text.MeasureEx();
  raylib::Vector2 texture_size = m_texture.GetSize();

  if (text_size.x > texture_size.x * TEXT_BUTTON_RATIO) {
    throw std::runtime_error("Text is too big for the button");
  }
}

// Button::Button(std::string_view text, rl::Font &customFont) {}

rl::Font &Button::defaultFont() {
  [[clang::always_destroy]] static rl::Font default_font(
      DEFAULT_FONT_PATH.data(), DEFAULT_FONT_SIZE, nullptr, DEFAULT_MAX_TEXT);
  return default_font;
}
rl::Texture &Button::defaultTexture() {
  // THIS MIGHT CAUSE A SIgSEV
  // the static texture is destroyed on exit time (when the program ends)
  // but, the window and graphics related stuff is destroyed earlier
  // could the be what is causing the sigv?
  static rl::Texture default_texture(DEFAULT_TEXTURE_PATH.data());
  return default_texture;
}

void Button::draw(const int &posX, const int &posY) const {

  auto text_size = m_text.MeasureEx();
  auto button_size = m_texture.GetSize();

  // clang-format off
  auto [text_x, text_y] = std::pair{
      posX +
          (static_cast<int>(button_size.x) - static_cast<int>(text_size.x)) / 2,
      posY +
          (static_cast<int>(button_size.y) - static_cast<int>(text_size.y)) / 2};
  // clang-format on

  m_texture.Draw(posX, posY);
  m_text.Draw(text_x, text_y);
}

bool Button::isClicked(const int &posX, const int &posY) const {

  if (!rl::Mouse::IsButtonPressed(MouseButton::MOUSE_LEFT_BUTTON)) {
    return false;
  }

  auto button_size = m_texture.GetSize();
  auto click_pos = rl::Mouse::GetPosition();

  std::cout << "Click pos: " << click_pos.x << ", " << click_pos.y << std::endl;

  // complicated stuff to check if click_pos is inside texture draw position
  // static_cast is used because rl::Vector2 is a float,
  // might not be needed, but affects performance?
  return static_cast<int>(click_pos.x) >= posX &&
         static_cast<int>(click_pos.x) <=
             posX + static_cast<int>(button_size.x) &&
         static_cast<int>(click_pos.y) >= posY &&
         static_cast<int>(click_pos.y) <=
             posY + static_cast<int>(button_size.y);
}
