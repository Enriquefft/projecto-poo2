#include "Bot.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
// enum class ALGORITHM { DFS, BFS, GBGS, A_STAR };

template <ALGORITHM T>
  requires IsDFSOrBFS<T>
void Bot::solve(const Board &board) {
  std::conditional_t<T == ALGORITHM::BFS, std::queue<square>,
                     std::stack<square>>
      frontier;

  square start = board.getStart();
  frontier.push(start);
  std::vector<square> explored;

  while (!frontier.empty()) {

    square current = frontier.top();
    frontier.pop();

    if (current == board.getEnd()) {
      break;
    }

    explored.push_back(current);

    for (square neighbor : board.getNeighbors(current)) {

      if (std::find(explored.begin(), explored.end(), neighbor) ==
          explored.end()) {
        frontier.push(neighbor);
        explored.push_back(neighbor);
      }
    }
  }
}
template <> void Bot::solve<ALGORITHM::BFS>(const Board &board) {}

template <> void Bot::solve<ALGORITHM::GBGS>(const Board &board) {}
template <> void Bot::solve<ALGORITHM::A_STAR>(const Board &board) {}

std::vector<square> Bot::getSolution() const { return m_solution; }
std::vector<square> Bot::getSearchedPath() const { return m_searchedPath; }
