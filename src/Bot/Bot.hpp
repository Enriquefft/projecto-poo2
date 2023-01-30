#ifndef BOT_H
#define BOT_H

#include "../Maze/Maze.hpp"

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
    requires IsDFSOrBFS<T> bool
  solve(const Maze &maze);

  template <ALGORITHM T>
    requires IsGBFSOrA_STAR<T> bool
  solve(const Maze &maze);


  [[nodiscard]] std::vector<square> getSolution() const;
  [[nodiscard]] std::vector<square> getSearchedPath() const;

private:
  std::vector<square> m_solution;
  std::vector<square> m_searchedPath;
};

// explicit instantiate solve
extern template bool Bot::solve<ALGORITHM::DFS>(const Maze &maze);
extern template bool Bot::solve<ALGORITHM::BFS>(const Maze &maze);
extern template bool Bot::solve<ALGORITHM::GBGS>(const Maze &maze);
extern template bool Bot::solve<ALGORITHM::A_STAR>(const Maze &maze);
#endif // !BOT_H
