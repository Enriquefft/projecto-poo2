#include <array>
#include <iostream>
#include <random>
#include <stdexcept>
#include <unordered_set>
#include <vector>

// Define a matrix for the maze
using Maze = std::vector<std::vector<char>>;

// Define a pair of coordinates for the current cell
using Coord = std::pair<int, int>;

// Define the direction vector for each cell
constexpr std::array<Coord, 4> dirs = {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

// Generate a random number in a range
int random_num(int min, int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(min, max);
  return dist(gen);
}

// Choose a random direction from the direction vector
Coord random_dir(const Coord &curr) {
  int idx = random_num(0, dirs.size() - 1);
  Coord next = curr;
  next.first += dirs[idx].first;
  next.second += dirs[idx].second;
  return next;
}

// Generate the maze using the Wilsons algorithm
Maze generate_maze(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Invalid number of rows or columns");
  }

  Maze maze(rows, std::vector<char>(cols, '#'));
  std::unordered_set<Coord> visited;

  // Choose a random starting point
  int start_row = random_num(0, rows - 1);
  int start_col = random_num(0, cols - 1);
  Coord curr = {start_row, start_col};
  visited.insert(curr);

  // Repeat until all cells have been visited
  while (visited.size() < rows * cols) {
    // Choose a random direction from the current cell
    Coord next = random_dir(curr);

    // Check if the next cell is within the boundaries and has not been visited
    if (next.first >= 0 && next.first < rows && next.second >= 0 &&
        next.second < cols && visited.count(next) == 0) {
      // Mark the current cell as visited and update the current cell
      visited.insert(next);
      maze[curr.first][curr.second] = ' ';
      curr = next;
    }
  }

  return maze;
}

int main() {
  try {
    int rows = 10;
    int cols = 10;
    Maze maze = generate_maze(rows, cols);

    // Print the generated maze
    for (const auto &row : maze) {
      for (const auto &cell : row) {
        std::cout << cell;
      }
      std::cout << '\n';
    }
  } catch (const std::invalid_argument &ex)
