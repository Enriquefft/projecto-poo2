#ifndef MAZE_HPP
#define MAZE_HPP

// #include "../Utils/Utils.h"
#include <cstdint>
#include <optional>
#include <ostream>
#include <unordered_map>
#include <vector>

enum class HUNT_METHOD { RANDOM, SERPENTINE };

constexpr HUNT_METHOD DEFAULT_HUNT_METHOD = HUNT_METHOD::SERPENTINE;

enum class SQUARE_TYPE { EMPTY, WALL, START, END, PATH, SEARCHED };
std::ostream &operator<<(std::ostream &ost, const SQUARE_TYPE &type);

using maze_t = std::vector<std::vector<SQUARE_TYPE>>;

using square = std::pair<uint8_t, uint8_t>;

using direction_t = std::pair<int8_t, int8_t>;
namespace DIRECTION {
constexpr direction_t NORTH = {-2, 0};
constexpr direction_t SOUTH = {2, 0};
constexpr direction_t EAST = {0, -2};
constexpr direction_t WEST = {0, 2};
} // namespace DIRECTION

class Maze {
public:
  Maze();
  Maze(uint8_t height, uint8_t width);
  void printMaze();
  [[nodiscard]] maze_t getMaze() const;

  [[nodiscard]] square getStart() const;
  [[nodiscard]] square getEnd() const;

  [[nodiscard]] std::vector<square> getNeighbors(const square &current) const;

  void paintPath(const std::vector<square> &path);
  void paintPath(const std::vector<square> &solution,
                 const std::vector<square> &searchedPath);

private:
  maze_t m_maze;
  uint8_t base_height;
  uint8_t base_width;

  square m_start;
  square m_goal;

  void generateMaze(uint8_t height, uint8_t width);

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

#endif // !MAZE_HPP
