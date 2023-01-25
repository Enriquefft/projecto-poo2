#include "Button.hpp"
#include <Vector2.hpp>

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
  [[clang::always_destroy]] static rl::Texture default_texture(
      DEFAULT_TEXTURE_PATH.data());
  return default_texture;
}
