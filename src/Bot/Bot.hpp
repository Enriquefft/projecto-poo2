#ifndef BOT_H
#define BOT_H

#include "../Board/Board.hpp"

enum class ALGORITHM { DFS, BFS, GBGS, A_STAR };

// clang-format off
template <ALGORITHM T>
concept IsDFSOrBFS = 
T == ALGORITHM::DFS ||
T == ALGORITHM::BFS;

class Bot {

public:
  Bot() = default;

  template <ALGORITHM T>
    requires IsDFSOrBFS<T> bool
  solve(const Board &board);

  template <ALGORITHM alg>
  bool solve(const Board &board) = delete;

  // gcc is not able to compile this

  template <> bool
  solve<ALGORITHM::GBGS>(const Board &board);
  template <> bool
  solve<ALGORITHM::A_STAR>(const Board &board);

  [[nodiscard]] std::vector<square> getSolution() const;
  [[nodiscard]] std::vector<square> getSearchedPath() const;

private:
  std::vector<square> m_solution;
  std::vector<square> m_searchedPath;
};

// explicit instantiate solve
extern template bool Bot::solve<ALGORITHM::DFS>(const Board &board);
extern template bool Bot::solve<ALGORITHM::BFS>(const Board &board);
#endif // !BOT_H
