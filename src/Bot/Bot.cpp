#include "Bot.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
// enum class ALGORITHM { DFS, BFS, GBGS, A_STAR };
// std::vector<square> m_solution;
// std::vector<square> m_searchedPath;

template <ALGORITHM T>
  requires IsDFSOrBFS<T> bool
Bot::solve(const Board &board) {
  m_solution.clear();
  m_searchedPath.clear();
  std::conditional_t<T == ALGORITHM::BFS, std::queue<square>,
                     std::stack<square>>
      frontier;

  square start = board.getStart();

  std::vector<square> explored;
  std::vector<square> parents;

  frontier.push(start);

  explored.push_back(start);
  parents.push_back(start);

  bool found = false;
  while (!frontier.empty()) {

    square current;
    if constexpr (T == ALGORITHM::DFS) {
      current = frontier.top();
    } else {
      current = frontier.front();
    }

    frontier.pop();

    if (current == board.getEnd()) {
      std::cout << "Found the end!" << std::endl;
      found = true;
      break;
    }

    explored.push_back(current);

    // std::cout << "Current: " << (int)current.first << "  "
    //           << (int)current.second << std::endl;
    for (square neighbor : board.getNeighbors(current)) {

      if (std::find(explored.begin(), explored.end(), neighbor) ==
          explored.end()) {
        // std::cout << "Neighbor: " << (int)neighbor.first << "  "
        //           << (int)neighbor.second << std::endl;
        frontier.push(neighbor);
        explored.push_back(neighbor);
        parents.push_back(current);
        m_searchedPath.push_back(neighbor);
      }
    }
  }
  if (!found) {
    std::cout << "No solution found" << std::endl;
    return false;
  }

  square current = board.getEnd();

  return true;
}

template <> bool Bot::solve<ALGORITHM::GBGS>(const Board &board) {
  return false;
}
template <> bool Bot::solve<ALGORITHM::A_STAR>(const Board &board) {
  return false;
}

std::vector<square> Bot::getSolution() const { return m_solution; }
std::vector<square> Bot::getSearchedPath() const { return m_searchedPath; }

// explicit instantiate solve
template bool Bot::solve<ALGORITHM::DFS>(const Board &board);
template bool Bot::solve<ALGORITHM::BFS>(const Board &board);
