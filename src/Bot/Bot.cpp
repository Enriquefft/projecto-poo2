#include "Bot.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>

template <ALGORITHM T>
  requires IsDFSOrBFS<T> bool
Bot::solve(const Maze &maze) {

  m_solution.clear();
  m_searchedPath.clear();

  square start = maze.getStart();

  std::conditional_t<T == ALGORITHM::BFS, std::queue<square>,
                     std::stack<square>>
      frontier;

  std::unordered_map<square, square, Maze::HashPair> parent;
  parent[start] = start;

  frontier.push(start);

  m_searchedPath.emplace(start);

  bool found = false;
  while (!frontier.empty()) {

    square current;
    if constexpr (T == ALGORITHM::DFS) {
      current = frontier.top();
    } else {
      current = frontier.front();
    }

    frontier.pop();

    if (current == maze.getGoal()) {
      std::cout << "Found the end!" << std::endl;
      found = true;
      break;
    }

    for (square neighbor : maze.getNeighbors(current)) {

      if (std::find(m_searchedPath.begin(), m_searchedPath.end(), neighbor) ==
          m_searchedPath.end()) {
        frontier.push(neighbor);
        m_searchedPath.emplace(neighbor);
        parent[neighbor] = current;
      }
    }
  }
  if (!found) {
    std::cout << "No solution found" << std::endl;
    return false;
    m_solution.clear();
  }

  square current = maze.getGoal();

  while (current != maze.getStart()) {

    m_solution.emplace(current);

    current = parent[current];
  }

  return true;
}

// Manhattan distance heuristic function
int Bot::heuristic(const square &current, const square &goal) {
  return std::abs(current.first - goal.first) +
         std::abs(current.second - goal.second);
}

template <> class Bot::Compare<ALGORITHM::GBGS> {
public:
  bool operator()(const square &sq1, const square &sq2) {
    if (!s_goal.has_value()) {
      throw std::runtime_error("Goal not set");
    }
    return heuristic(sq1, Bot::s_goal.value()) >
           heuristic(sq2, Bot::s_goal.value());
  }
};

template <> class Bot::Compare<ALGORITHM::A_STAR> {
public:
  bool operator()(const Node &sq1, const Node &sq2) {
    if (!s_goal.has_value()) {
      throw std::runtime_error("Goal not set");
    }
    return heuristic(sq1, Bot::s_goal.value()) + sq1.w_score >
           heuristic(sq2, Bot::s_goal.value()) + sq2.w_score;
  }
};

Bot::Node::Node(const square &pos, const int &score)
    : square(pos), w_score(score) {}

bool Bot::Node::operator==(const square &sqr) {
  return sqr.first == first && sqr.second == second;
}

template <> bool Bot::solve<ALGORITHM::A_STAR>(const Maze &maze) {

  std::cout << "Solving with A*" << std::endl;

  m_solution.clear();
  m_searchedPath.clear();
  s_goal = maze.getGoal();

  auto start = maze.getStart();

  std::priority_queue<Node, std::vector<Node>, Compare<ALGORITHM::A_STAR>>
      frontier;

  std::unordered_map<square, square, Maze::HashPair> parent;

  parent[start] = start;

  frontier.push(start);

  m_searchedPath.emplace(start);

  bool found = false;

  square current;

  while (!frontier.empty()) {

    current = frontier.top();
    int current_score = frontier.top().w_score;

    frontier.pop();

    if (current == maze.getGoal()) {
      std::cout << "Found the end!" << std::endl;
      found = true;
      break;
    }

    m_searchedPath.emplace(current);
    for (square neighbor : maze.getNeighbors(current)) {

      if (std::find(m_searchedPath.begin(), m_searchedPath.end(), neighbor) ==
          m_searchedPath.end()) {
        m_searchedPath.emplace(current);
        frontier.emplace(neighbor, current_score + 1);
        parent[neighbor] = current;
      }
    }
  }
  if (!found) {
    std::cout << "No solution found" << std::endl;
    m_searchedPath.clear();
    return false;
  }

  square current_sq = maze.getGoal();
  while (current_sq != maze.getStart()) {
    m_solution.emplace(current_sq);
    current_sq = parent[current_sq];
  }

  return true;
}

template <> bool Bot::solve<ALGORITHM::GBGS>(const Maze &maze) {

  std::cout << "Solving with Greedy Best First Search" << std::endl;

  m_solution.clear();
  m_searchedPath.clear();
  s_goal = maze.getGoal();

  auto start = maze.getStart();

  std::priority_queue<square, std::vector<square>, Compare<ALGORITHM::GBGS>>
      frontier;

  std::unordered_map<square, square, Maze::HashPair> parent;

  parent[start] = start;

  frontier.push(start);

  m_searchedPath.emplace(start);

  bool found = false;

  square current;

  while (!frontier.empty()) {

    current = frontier.top();
    frontier.pop();

    if (current == maze.getGoal()) {
      std::cout << "Found the end!" << std::endl;
      found = true;
      break;
    }

    m_searchedPath.emplace(current);
    for (square neighbor : maze.getNeighbors(current)) {

      if (std::find(m_searchedPath.begin(), m_searchedPath.end(), neighbor) ==
          m_searchedPath.end()) {
        m_searchedPath.emplace(current);
        frontier.push(neighbor);
        parent[neighbor] = current;
      }
    }
  }
  if (!found) {
    std::cout << "No solution found" << std::endl;
    m_searchedPath.clear();
    return false;
  }

  square current_sq = maze.getGoal();
  while (current_sq != maze.getStart()) {
    m_solution.emplace(current_sq);
    current_sq = parent[current_sq];
  }

  return true;
}

template <bool hasNode> void PrintPriorityQueue(const auto &queue) {
  auto copy = queue;
  std::cout << "Priority Queue: \n";
  if constexpr (hasNode) {
    while (!copy.empty()) {
      std::cout << copy.top().first << " " << copy.top().second << std::endl;
      std::cout << "Score: " << copy.top().w_score << std::endl;
      copy.pop();
    }
  } else {
    while (!copy.empty()) {
      std::cout << copy.top().first << " " << copy.top().second << std::endl;
      copy.pop();
    }
  }
}

std::unordered_set<square, Maze::HashPair> Bot::getSolution() const {
  return m_solution;
}
std::unordered_set<square, Maze::HashPair> Bot::getSearchedPath() const {
  return m_searchedPath;
}

// explicit instantiate solve
// template bool Bot::solve<ALGORITHM::DFS>(const Maze &maze);
// template bool Bot::solve<ALGORITHM::BFS>(const Maze &maze);
// template bool Bot::solve<ALGORITHM::GBGS>(const Maze &maze);
// template bool Bot::solve<ALGORITHM::A_STAR>(const Maze &maze);
