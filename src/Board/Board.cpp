#include "Board.h"
#include "../Utils/Utils.h"
#include <cstdint>

constexpr uint8_t MAX_WIDTH = 42;
constexpr uint8_t MIN_WIDTH = 21;
constexpr uint8_t MAX_HEIGHT = 30;
constexpr uint8_t MIN_HEIGHT = 15;

Board::Board() {
  auto height = Utils::RandomNum<uint8_t>(MIN_HEIGHT, MAX_HEIGHT);
  uint8_t width = Utils::RandomNum<uint8_t>(MAX_WIDTH, MAX_WIDTH);

  // Generate random maze using kruskal's random algorithm (random weights)
}
Board::Board(uint8_t height, uint8_t width) {}
