#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

namespace Utils {

struct Space {
  // TEMPORARY DEFINITION
  // Remove and make its own module
  // TODO(enrique):
public:
  explicit Space(uint8_t value) : value(value) {}
  uint8_t value;
  void operator=(uint8_t value) { this->value = value; }
};

// USING ALIASES
using board_t = std::vector<std::vector<Space>>;

template <std::integral T> T RandomNum(const T &min, const T &max);
template <std::floating_point T> T RandomNum(const T &min, const T &max);

template <std::unsigned_integral T>
inline constexpr auto UnsignedToSigned(const T &value) {
  auto max = std::numeric_limits<std::make_signed_t<T>>::max();
  if (value > static_cast<T>(max)) {
    throw std::out_of_range("Value is out of range");
  }
  return static_cast<std::make_signed_t<T>>(value);
}

template <std::signed_integral T>
inline constexpr auto SignedToUnsigned(const T &value) {
  if (value < 0) {
    throw std::invalid_argument("Value must be positive");
  }
  return static_cast<std::make_unsigned_t<T>>(value);
}

extern template uint8_t RandomNum<uint8_t>(const uint8_t &min,
                                           const uint8_t &max);
extern template unsigned char
RandomNum<unsigned char>(const unsigned char &min, const unsigned char &max);

} // namespace Utils

#endif // !UTILS_H
