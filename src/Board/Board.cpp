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
}

void Board::printBoard() {
  std::cout << "Board:" << std::endl;

  for (auto &row : m_maze) {
    for (auto &col : row) {
      std::cout << col.value;
    }
    std::cout << std::endl;
  }
}

template <>
std::pair<uint8_t, uint8_t>
Board::hunt<HUNT_METHOD::RANDOM>(const uint8_t &count) {
  if (count >= base_height * base_width) {
    return std::make_pair(0, 0);
  }
  // TODO(enrique): Implement randrange
  throw std::runtime_error("Not implemented");
}
template <>
std::pair<uint8_t, uint8_t>
Board::hunt<HUNT_METHOD::SERPENTINE>(const uint8_t &count) {
  // TODO(enrique): Implement serpentine
  throw std::runtime_error("Not implemented");
}

std::unordered_map<square, DIRECTION> Board::randomWalk(const square &start) {
  // TODO(enrique): Implement random walk
  throw std::runtime_error("Not implemented");
}
DIRECTION Board::randomDirection(const square &current) {
  // TODO(enrique): Implement random direction
  throw std::runtime_error("Not implemented");
}
DIRECTION Board::move(const square &current, const DIRECTION &direction) {
  // TODO(enrique): Implement move
  throw std::runtime_error("Not implemented");
}

uint8_t
Board::solveRandomWalk(const std::unordered_map<square, DIRECTION> &walk,
                       const square &start) {
  // TODO(enrique): Implement solve random walk
  throw std::runtime_error("Not implemented");
}
