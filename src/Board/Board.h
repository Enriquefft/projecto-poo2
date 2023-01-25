#ifndef BOARD_H
#define BOARD_H

#include "../Utils/Utils.h"
#include <cstdint>
#include <unordered_map>

enum class HUNT_METHOD { RANDOM, SERPENTINE };

constexpr HUNT_METHOD DEFAULT_HUNT_METHOD = HUNT_METHOD::RANDOM;

using square = std::pair<uint8_t, uint8_t>;

namespace DIRECTION {

constexpr square NORTH = {-2, 0};
constexpr square SOUTH = {2, 0};
constexpr square EAST = {0, -2};
constexpr square WEST = {0, 2};
} // namespace DIRECTION
using direction_t = square;

class Board {
public:
  Board();
  Board(uint8_t height, uint8_t width);
  void printBoard();

private:
  Utils::board_t m_maze;
  uint8_t base_height;
  uint8_t base_width;

  void generateBoard(uint8_t height, uint8_t width);

  template <HUNT_METHOD = DEFAULT_HUNT_METHOD>
  square hunt(const uint8_t &count) = delete;

  std::unordered_map<square, direction_t> randomWalk(const square &start);
  direction_t randomDirection(const square &current);
  direction_t move(const square &current, const direction_t &direction);

  uint8_t solveRandomWalk(const std::unordered_map<square, direction_t> &walk,
                          const square &start);
};

#endif // !BOARD_H
