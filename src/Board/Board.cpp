#include "Board.h"
#include "../Utils/Utils.h"
#include <algorithm>
#include <random>

// Testing
#include <cstdint>
#include <iostream>
#include <sys/types.h>

constexpr uint8_t MAX_WIDTH = 21;
constexpr uint8_t MIN_WIDTH = 10;
constexpr uint8_t MAX_HEIGHT = 15;
constexpr uint8_t MIN_HEIGHT = 7;

// First ineficient implementation
Board::Board(uint8_t customHeight, uint8_t customWidth)
    : base_height(customHeight), base_width(customWidth) {
  uint8_t height = base_height * 2 + 1;
  uint8_t width = base_width * 2 + 1;

  generateBoard(height, width);
}
Board::Board()
    : base_height(Utils::RandomNum<uint8_t>(MIN_HEIGHT, MAX_HEIGHT)),
      base_width(Utils::RandomNum<uint8_t>(MIN_WIDTH, MAX_WIDTH)) {

  uint8_t height = base_height * 2 + 1;
  uint8_t width = base_width * 2 + 1;

  generateBoard(height, width);
}

// Methods to hunt next square
template <>
std::optional<square> Board::hunt<HUNT_METHOD::RANDOM>(const uint8_t &count);
template <>
std::optional<square>
Board::hunt<HUNT_METHOD::SERPENTINE>(const uint8_t &count);

void Board::generateBoard(uint8_t height, uint8_t width) {
  // Allocate memory for the board
  m_maze.resize(height);
  for (auto &row : m_maze) {
    for (auto i = 0; i < width; i++) {
      row.emplace_back(1);
    }
  }

  uint8_t start_x = 0;
  uint8_t start_y = 0;

  do {
    start_x = Utils::RandomNum<uint8_t>(0, height);
  } while (start_x % 2 == 1);
  do {
    start_y = Utils::RandomNum<uint8_t>(0, width);
  } while (start_y % 2 == 1);

  m_maze[start_x][start_y] = 0;

  uint8_t visit_count = 1;

  auto first_hunt_opt = hunt(visit_count);

  while (first_hunt_opt.has_value()) {
    auto [row, col] = first_hunt_opt.value();
    auto walk = randomWalk({row, col});
    visit_count = solveRandomWalk(walk, {row, col});
    first_hunt_opt = hunt(visit_count);
  }
}

void Board::printBoard() {
  std::cout << "Board:" << std::endl;

  for (auto &row : m_maze) {
    for (auto &elem : row) {
      if (elem == 1) {
        std::cout << "██";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << std::endl;
  }
}

template <>
std::optional<square> Board::hunt<HUNT_METHOD::RANDOM>(const uint8_t &count) {

  if (count >= base_height * base_width) {
    return std::make_pair(-1, -1);
  }

  uint8_t row = 0;
  uint8_t col = 0;

  do {
    row = Utils::RandomNum<uint8_t>(0, static_cast<uint8_t>(m_maze.size()));
  } while (row % 2 == 1);

  do {
    col = Utils::RandomNum<uint8_t>(0, static_cast<uint8_t>(m_maze[0].size()));
  } while (col % 2 == 1);

  return std::make_pair(row, col);
}

template <>
std::optional<square>
Board::hunt<HUNT_METHOD::SERPENTINE>(const uint8_t &count) {
  // TODO(enrique): Implement serpentine
  throw std::runtime_error("Not implemented");
}

template <class T1, class T2>
size_t Board::HashPair::operator()(const std::pair<T1, T2> &pair) const {
  // https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/
  auto hash1 = std::hash<T1>{}(pair.first);
  auto hash2 = std::hash<T2>{}(pair.second);

  if (hash1 != hash2) {
    return hash1 ^ hash2;
  }

  // If hash1 == hash2, their XOR is zero.
  return hash1;
}

std::unordered_map<square, direction_t, Board::HashPair>
Board::randomWalk(const square &start) {

  direction_t direction = randomDirection(start);
  std::unordered_map<square, direction_t, Board::HashPair> walk;
  walk[start] = direction;

  auto current = move(start, direction);

  while (m_maze[current.first][current.second] == 1) {
    direction = randomDirection(current);
    walk[current] = direction;
    current = move(current, direction);
  }
  return walk;
}
direction_t Board::randomDirection(const square &current) {

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

direction_t Board::move(const square &current, const direction_t &direction) {
  return {current.first + direction.first, current.second + direction.second};
}

uint8_t Board::solveRandomWalk(
    const std::unordered_map<square, direction_t, HashPair> &walk,
    const square &start) {

  uint8_t count = 0;

  square current = start;

  while (m_maze[current.first][current.second] != 0) {
    m_maze[current.first][current.second] = 0;
    direction_t next = move(current, walk.at(current));
    uint8_t new_x = (next.first + current.first) / 2;
    uint8_t new_y = (next.second + current.second) / 2;
    m_maze[new_x][new_y] = 0;
    count++;
    current = next;
  }
  return count;
}
