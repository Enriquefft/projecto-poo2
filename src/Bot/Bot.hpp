#ifndef BOT_H
#define BOT_H

#include "../Board/Board.hpp"

enum class ALGORITHM { DFS, BFS, GBGS, A_STAR };

template <ALGORITHM T>
concept IsDFSOrBFS = T ==
ALGORITHM::DFS || T == ALGORITHM::BFS;

class Bot {

public:
  Bot() = default;

  template <ALGORITHM T>
    requires IsDFSOrBFS<T> bool
  solve(const Board &board);

  template <ALGORITHM alg> bool solve(const Board &board) = delete;

  [[nodiscard]] std::vector<square> getSolution() const;
  [[nodiscard]] std::vector<square> getSearchedPath() const;

private:
  std::vector<square> m_solution;
  std::vector<square> m_searchedPath;
};

#endif // !BOT_H
