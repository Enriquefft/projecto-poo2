#include "Maze.hpp"
#include <algorithm>
#include <random>

#include "../Utils/Utils.h"

// Testing
#include <cstdint>
#include <iostream>
#include <sys/types.h>

constexpr uint8_t MAX_WIDTH = 21;
constexpr uint8_t MIN_WIDTH = 10;
constexpr uint8_t MAX_HEIGHT = 15;
constexpr uint8_t MIN_HEIGHT = 7;

Maze::Maze(uint8_t customHeight, uint8_t customWidth)
    : base_height(customHeight), base_width(customWidth) {
  uint8_t height = base_height * 2 + 1;
  uint8_t width = base_width * 2 + 1;

  generateMaze(height, width);
}
Maze::Maze()
    : base_height(Utils::RandomNum<uint8_t>(MIN_HEIGHT, MAX_HEIGHT)),
      base_width(Utils::RandomNum<uint8_t>(MIN_WIDTH, MAX_WIDTH)) {

  uint8_t height = base_height * 2 + 1;
  uint8_t width = base_width * 2 + 1;

  generateMaze(height, width);
}

// Methods to hunt next square
template <>
std::optional<square> Maze::hunt<HUNT_METHOD::RANDOM>(const uint8_t &count);
template <>
std::optional<square> Maze::hunt<HUNT_METHOD::SERPENTINE>(const uint8_t &count);

void Maze::generateMaze(uint8_t height, uint8_t width) {

  // generate matrix of walls
  m_maze = std::vector<std::vector<SQUARE_TYPE>>(
      height, std::vector<SQUARE_TYPE>(width, SQUARE_TYPE::WALL));

  uint8_t start_x = 0;
  uint8_t start_y = 0;

  do {
    start_x = Utils::RandomNum<uint8_t>(1, height - 1);
  } while (start_x % 2 != 1);
  do {
    start_y = Utils::RandomNum<uint8_t>(1, width - 1);
  } while (start_y % 2 != 1);

  m_maze[start_x][start_y] = SQUARE_TYPE::EMPTY;

  uint8_t visit_count = 1;

  auto first_hunt_opt = hunt(visit_count);

  while (first_hunt_opt.has_value()) {
    auto [row, col] = first_hunt_opt.value();
    auto walk = randomWalk({row, col});

    visit_count += solveRandomWalk(walk, {row, col});
    first_hunt_opt = hunt(visit_count);
    // printMaze();
  }

  do {
    start_x = Utils::RandomNum<uint8_t>(1, height - 1);
    start_y = Utils::RandomNum<uint8_t>(1, width - 1);
  } while (m_maze[start_x][start_y] != SQUARE_TYPE::EMPTY);
  m_maze[start_x][start_y] = SQUARE_TYPE::START;
  m_start = {start_x, start_y};

  uint8_t end_x = 0;
  uint8_t end_y = 0;
  // END
  do {
    end_x = Utils::RandomNum<uint8_t>(1, height - 1);
    end_y = Utils::RandomNum<uint8_t>(1, width - 1);
  } while (m_maze[end_x][end_y] != SQUARE_TYPE::EMPTY);
  m_maze[end_x][end_y] = SQUARE_TYPE::END;
  m_goal = {end_x, end_y};
}

void Maze::printMaze() {
  std::cout << "Maze:" << std::endl;

  for (auto &row : m_maze) {
    for (auto &elem : row) {
      std::cout << elem;
    }
    std::cout << std::endl;
  }
}

template <>
std::optional<square> Maze::hunt<HUNT_METHOD::RANDOM>(const uint8_t &count) {
  // CHECKED

  if (count >= base_height * base_width) {
    return std::nullopt;
  }

  uint8_t row = 0;
  uint8_t col = 0;

  do {
    row = Utils::RandomNum<uint8_t>(1, static_cast<uint8_t>(m_maze.size() - 1));
  } while (row % 2 != 1);

  do {
    col = Utils::RandomNum<uint8_t>(1,
                                    static_cast<uint8_t>(m_maze[0].size() - 1));
  } while (col % 2 != 1);

  return std::make_pair(row, col);
}

template <>
std::optional<square>
Maze::hunt<HUNT_METHOD::SERPENTINE>(const uint8_t & /*count*/) {

  /*
             cell = (1, -1)
        found = False

        while not found:
            cell = (cell[0], cell[1] + 2)
            if cell[1] > (self.W - 2):
                cell = (cell[0] + 2, 1)
                if cell[0] > (self.H - 2):
                    return (-1, -1)

            if grid[cell[0]][cell[1]] != 0:
                found = True

        return cell

    */

  std::pair<int8_t, int8_t> cell = {1, -1};
  bool found = false;

  while (!found) {
    cell.second += 2;
    if (cell.second > static_cast<int8_t>(m_maze[0].size() - 2)) {
      cell.first += 2;
      cell.second = 1;
      if (cell.first > static_cast<int8_t>(m_maze.size() - 2)) {
        return std::nullopt;
      }
    }

    if (m_maze[static_cast<uint8_t>(cell.first)]
              [static_cast<uint8_t>(cell.second)] != SQUARE_TYPE::EMPTY) {
      found = true;
    }
  }

  // if is valid cell
  if (cell.first >= 0 && cell.second >= 0 &&
      cell.first < static_cast<int8_t>(m_maze.size()) &&
      cell.second < static_cast<int8_t>(m_maze[0].size())) {
    return std::make_pair(static_cast<uint8_t>(cell.first),
                          static_cast<uint8_t>(cell.second));
  }
  throw std::runtime_error("Invalid cell");
}

template <class T1, class T2>
size_t Maze::HashPair::operator()(const std::pair<T1, T2> &pair) const {
  // https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/
  auto hash1 = std::hash<T1>{}(pair.first);
  auto hash2 = std::hash<T2>{}(pair.second);

  if (hash1 != hash2) {
    return hash1 ^ hash2;
  }

  // If hash1 == hash2, their XOR is zero.
  return hash1;
}

std::unordered_map<square, direction_t, Maze::HashPair>
Maze::randomWalk(const square &start) {
  // ERROR HERE??

  direction_t direction = randomDirection(start);
  std::unordered_map<square, direction_t, Maze::HashPair> walk;
  walk[start] = direction;

  auto current = move(start, direction);

  while (m_maze[current.first][current.second] == SQUARE_TYPE::WALL) {
    direction = randomDirection(current);
    walk[current] = direction;
    current = move(current, direction);
  }
  return walk;
}

direction_t Maze::randomDirection(const square &current) {
  // CHECKED

  auto [row, col] = current;

  std::vector<direction_t> directions;

  if (row > 1) {
    directions.emplace_back(DIRECTION::NORTH);
  }
  if (row < m_maze.size() - 2) {
    directions.emplace_back(DIRECTION::SOUTH);
  }
  if (col > 1) {
    directions.emplace_back(DIRECTION::EAST);
  }
  if (col < m_maze[0].size() - 2) {
    directions.emplace_back(DIRECTION::WEST);
  }

  return directions[Utils::RandomNum<size_t>(0, directions.size() - 1)];
}

square Maze::move(const square &current, const direction_t &direction) {
  return {current.first + direction.first, current.second + direction.second};
}

uint8_t Maze::solveRandomWalk(
    const std::unordered_map<square, direction_t, HashPair> &walk,
    const square &start) {

  uint8_t count = 0;

  square current = start;

  while (m_maze[current.first][current.second] != SQUARE_TYPE::EMPTY) {
    m_maze[current.first][current.second] = SQUARE_TYPE::EMPTY;
    square next = move(current, walk.at(current));
    uint8_t new_x = (next.first + current.first) / 2;
    uint8_t new_y = (next.second + current.second) / 2;
    m_maze[new_x][new_y] = SQUARE_TYPE::EMPTY;
    count++;
    current = next;
  }
  return count;
}

maze_t Maze::getMaze() const { return m_maze; }
square Maze::getStart() const { return m_start; }
square Maze::getEnd() const { return m_goal; }

std::vector<square> Maze::getNeighbors(const square &current) const {

  auto [row, col] = current;

  std::vector<square> neighbors;

  if (row > 0 && m_maze[row - 1][col] != SQUARE_TYPE::WALL) {
    neighbors.emplace_back(row - 1, col);
  }
  if (row < m_maze.size() - 1 && m_maze[row + 1][col] != SQUARE_TYPE::WALL) {
    neighbors.emplace_back(row + 1, col);
  }
  if (col > 0 && m_maze[row][col - 1] != SQUARE_TYPE::WALL) {
    neighbors.emplace_back(row, col - 1);
  }
  if (col < m_maze[0].size() - 1 && m_maze[row][col + 1] != SQUARE_TYPE::WALL) {
    neighbors.emplace_back(row, col + 1);
  }

  return neighbors;
}

void Maze::paintPath(const std::vector<square> &path) {
  for (const auto &sqr : path) {
    if (m_maze[sqr.first][sqr.second] != SQUARE_TYPE::START &&
        m_maze[sqr.first][sqr.second] != SQUARE_TYPE::END) {
      m_maze[sqr.first][sqr.second] = SQUARE_TYPE::PATH;
    }
  }
}
void Maze::paintPath(const std::vector<square> &solution,
                     const std::vector<square> &searchedPath) {
  for (const auto &sqr : solution) {
    if (m_maze[sqr.first][sqr.second] != SQUARE_TYPE::START &&
        m_maze[sqr.first][sqr.second] != SQUARE_TYPE::END) {
      m_maze[sqr.first][sqr.second] = SQUARE_TYPE::PATH;
    }
  }
  for (const auto &sqr : searchedPath) {
    if (m_maze[sqr.first][sqr.second] != SQUARE_TYPE::START &&
        m_maze[sqr.first][sqr.second] != SQUARE_TYPE::END &&
        m_maze[sqr.first][sqr.second] != SQUARE_TYPE::PATH) {
      m_maze[sqr.first][sqr.second] = SQUARE_TYPE::SEARCHED;
    }
  }
}

std::ostream &operator<<(std::ostream &ost, const SQUARE_TYPE &type) {
  switch (type) {
  case SQUARE_TYPE::WALL:
    ost << "██";
    break;
  case SQUARE_TYPE::EMPTY:
    ost << "  ";
    break;
  case SQUARE_TYPE::START:
    ost << "";
    break;
  case SQUARE_TYPE::END:
    ost << " ";
    break;
  case SQUARE_TYPE::PATH:
    ost << " ";
    break;
  case SQUARE_TYPE::SEARCHED:
    ost << " ";
    break;
  }
  return ost;
}