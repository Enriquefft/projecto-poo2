#include "Button.hpp"

Button::Button(std::string_view text, rl::Texture &customTexture,
               float fontSize, const rl::Color &color)
    : m_text(rl::Text(text.data(), fontSize, color)), m_texture(customTexture) {
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
