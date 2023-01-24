#ifndef BOARD_H
#define BOARD_H

#include "../Utils/Utils.h"
#include <cstdint>
#include <unordered_map>

enum class HUNT_METHOD { RANDOM, SERPENTINE };
constexpr HUNT_METHOD DEFAULT_HUNT_METHOD = HUNT_METHOD::RANDOM;

enum class DIRECTION { NORTH, EAST, SOUTH, WEST };

using square = std::pair<uint8_t, uint8_t>;

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

  std::unordered_map<square, DIRECTION> randomWalk(const square &start);
  DIRECTION randomDirection(const square &current);
  DIRECTION move(const square &current, const DIRECTION &direction);

  uint8_t solveRandomWalk(const std::unordered_map<square, DIRECTION> &walk,
                          const square &start);
};

#endif // !BOARD_H
