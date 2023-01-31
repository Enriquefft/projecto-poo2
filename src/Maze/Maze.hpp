#ifndef MAZE_HPP
#define MAZE_HPP

// #include "../Utils/Utils.h"
#include <cstdint>
#include <optional>
#include <ostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum class HUNT_METHOD { RANDOM, SERPENTINE };

constexpr HUNT_METHOD DEFAULT_HUNT_METHOD = HUNT_METHOD::SERPENTINE;

enum class SQUARE_TYPE { EMPTY, WALL, START, GOAL, PATH, SEARCHED };
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
  struct HashPair;

  explicit Maze(maze_t &maze);
  explicit Maze(HUNT_METHOD huntMethod = DEFAULT_HUNT_METHOD);
  Maze(uint8_t height, uint8_t width,
       HUNT_METHOD huntMethod = DEFAULT_HUNT_METHOD);

  void printMaze();
  [[nodiscard]] maze_t getMaze() const;

  [[nodiscard]] constexpr square getStart() const { return m_start; }
  [[nodiscard]] constexpr square getGoal() const { return m_goal; }

  [[nodiscard]] std::vector<square> getNeighbors(const square &current) const;

  void paintPath(const std::unordered_set<square, HashPair> &path);
  void paintPath(const std::unordered_set<square, HashPair> &solution,
                 const std::unordered_set<square, HashPair> &searchedPath);

  struct HashPair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2> &pair) const;
  };

private:
  maze_t m_maze;
  uint8_t base_height;
  uint8_t base_width;

  square m_start;
  square m_goal;

  [[nodiscard]] bool isValidSquare(const SQUARE_TYPE &current) const;

  void generateMaze(uint8_t height, uint8_t width, HUNT_METHOD huntMethod);

  template <HUNT_METHOD>
  std::optional<square> hunt(const std::optional<uint8_t> &count);

  std::unordered_map<square, direction_t, HashPair>
  randomWalk(const square &start);

  direction_t randomDirection(const square &current);

  static square move(const square &current, const direction_t &direction);

  uint8_t
  solveRandomWalk(const std::unordered_map<square, direction_t, HashPair> &walk,
                  const square &start);
};

#endif // !MAZE_HPP
