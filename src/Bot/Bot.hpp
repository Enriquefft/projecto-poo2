#ifndef BOT_H
#define BOT_H

#include "../Maze/Maze.hpp"
#include <unordered_set>

enum class ALGORITHM { DFS, BFS, GBGS, A_STAR };

// clang-format off
template <ALGORITHM T>
concept IsDFSOrBFS = 
T == ALGORITHM::DFS ||
T == ALGORITHM::BFS;

template <ALGORITHM T>
concept IsGBFSOrA_STAR = 
T == ALGORITHM::GBGS ||
T == ALGORITHM::A_STAR;

class Bot {

public:
  Bot() = default;

  template <ALGORITHM T>
  bool solve(const Maze &maze);

  template <ALGORITHM T>
    requires IsDFSOrBFS<T> bool
  solve(const Maze &maze);

  [[nodiscard]] std::unordered_set<square, Maze::HashPair> getSolution() const;
  [[nodiscard]] std::unordered_set<square, Maze::HashPair> getSearchedPath() const;

private:

  struct Node: public square{
    Node() = default;
    Node(const square &pos, const int &score = 0); //NOLINT
    bool operator==(const square &sqr);

    int w_score{};

  };

  std::unordered_set<square, Maze::HashPair> m_solution;
  std::unordered_set<square, Maze::HashPair> m_searchedPath;

  inline static std::optional<square> s_goal = std::nullopt;

  template <ALGORITHM T>
  class Compare;

  [[nodiscard]] static int heuristic(const square &current, const square &goal);


};

// explicit instantiate solve
// extern template bool Bot::solve<ALGORITHM::DFS>(const Maze &maze);
// extern template bool Bot::solve<ALGORITHM::BFS>(const Maze &maze);
// extern template bool Bot::solve<ALGORITHM::GBGS>(const Maze &maze);
// extern template bool Bot::solve<ALGORITHM::A_STAR>(const Maze &maze);
#endif // !BOT_H
