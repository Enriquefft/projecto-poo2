#ifndef BOARD_HPP
#define BOARD_HPP

// #include "../Utils/Utils.h"
#include <cstdint>
#include <optional>
#include <ostream>
#include <unordered_map>
#include <vector>

enum class HUNT_METHOD { RANDOM, SERPENTINE };

constexpr HUNT_METHOD DEFAULT_HUNT_METHOD = HUNT_METHOD::RANDOM;

enum class SQUARE_TYPE : uint8_t {
  EMPTY = 0,
  WALL = 1,
  START = 2,
  END = 3,
  PATH = 4
};
std::ostream &operator<<(std::ostream &ost, const SQUARE_TYPE &type);

using board_t = std::vector<std::vector<SQUARE_TYPE>>;

using square = std::pair<uint8_t, uint8_t>;

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
  [[nodiscard]] board_t getBoard() const;

  [[nodiscard]] square getStart() const;
  [[nodiscard]] square getEnd() const;

  [[nodiscard]] std::vector<square> getNeighbors(const square &current) const;

  void paintPath(const std::vector<square> &path);

private:
  board_t m_maze;
  uint8_t base_height;
  uint8_t base_width;

  square m_start;
  square m_goal;

  void generateBoard(uint8_t height, uint8_t width);
  void notNaziGenerate();

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

#endif // !BOARD_HPP
