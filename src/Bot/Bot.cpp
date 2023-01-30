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
Bot::solve(const Maze &maze) {

  struct Node {
    square m_square;
    square m_parent;
  };

  m_solution.clear();
  m_searchedPath.clear();

  std::conditional_t<T == ALGORITHM::BFS, std::queue<square>,
                     std::stack<square>>
      frontier;

  square start = maze.getStart();

  std::vector<Node> parents;
  parents.push_back({start, start});

  frontier.push(start);

  m_searchedPath.push_back(start);

  bool found = false;
  while (!frontier.empty()) {

    square current;
    if constexpr (T == ALGORITHM::DFS) {
      current = frontier.top();
    } else {
      current = frontier.front();
    }

    frontier.pop();

    if (current == maze.getEnd()) {
      std::cout << "Found the end!" << std::endl;
      found = true;
      break;
    }

    for (square neighbor : maze.getNeighbors(current)) {

      if (std::find(m_searchedPath.begin(), m_searchedPath.end(), neighbor) ==
          m_searchedPath.end()) {
        frontier.push(neighbor);
        m_searchedPath.push_back(neighbor);
        parents.push_back({neighbor, current});
      }
    }
  }
  if (!found) {
    std::cout << "No solution found" << std::endl;
    return false;
    m_solution.clear();
  }

  square current = maze.getEnd();
  while (current != maze.getStart()) {
    m_solution.push_back(current);
    auto itt =
        std::find_if(parents.begin(), parents.end(), [&](const Node &node) {
          return node.m_square == current;
        });
    current = itt->m_parent;
  }

  return true;
}

template <ALGORITHM T>
  requires IsGBFSOrA_STAR<T> bool
Bot::solve(const Maze & /*maze*/) {
  std::cout << "GBGS or astar" << std::endl;
  return false;
}

// template <> bool Bot::solve<ALGORITHM::GBGS>(const Maze & /*maze*/) {
//   std::cout << "GBGS" << std::endl;
//   return false;
// }
// template <> bool Bot::solve<ALGORITHM::A_STAR>(const Maze & /*maze*/) {
//   std::cout << "A_STAR" << std::endl;
//   return false;
// }

std::vector<square> Bot::getSolution() const { return m_solution; }
std::vector<square> Bot::getSearchedPath() const { return m_searchedPath; }

// explicit instantiate solve
template bool Bot::solve<ALGORITHM::DFS>(const Maze &maze);
template bool Bot::solve<ALGORITHM::BFS>(const Maze &maze);
template bool Bot::solve<ALGORITHM::GBGS>(const Maze &maze);
template bool Bot::solve<ALGORITHM::A_STAR>(const Maze &maze);
