#ifndef BOARD_H
#define BOARD_H

// #include "../Utils/Utils.h"
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <vector>

enum class HUNT_METHOD { RANDOM, SERPENTINE };

constexpr HUNT_METHOD DEFAULT_HUNT_METHOD = HUNT_METHOD::RANDOM;

using square = std::pair<uint8_t, uint8_t>;
using Space = int;

using board_t = std::vector<std::vector<Space>>;

using direction_t = std::pair<int8_t, int8_t>;
namespace DIRECTION {
constexpr direction_t NORTH = {-2, 0};
constexpr direction_t SOUTH = {2, 0};
constexpr direction_t EAST = {0, -2};
constexpr direction_t WEST = {0, 2};
} // namespace DIRECTION

class Board {
public:
  Board();
  Board(uint8_t height, uint8_t width);
  void printBoard();

  // private:

  board_t m_maze;
  uint8_t base_height;
  uint8_t base_width;

  void generateBoard(uint8_t height, uint8_t width);

  template <HUNT_METHOD = DEFAULT_HUNT_METHOD>
  std::optional<square> hunt(const uint8_t &count);

  struct HashPair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2> &pair) const;
  };
  std::unordered_map<square, direction_t, HashPair>
  randomWalk(const square &start);
  direction_t randomDirection(const square &current);
  static square move(const square &current, const direction_t &direction);

  uint8_t
  solveRandomWalk(const std::unordered_map<square, direction_t, HashPair> &walk,
                  const square &start);
};

#endif // !BOARD_H
