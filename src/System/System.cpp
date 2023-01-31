#include "System.hpp"
#include "../Bot/Bot.hpp"
#include "../Maze/Maze.hpp"

void System::run() {

  // m_vista.startScreen();

  SQUARE_TYPE W = SQUARE_TYPE::WALL;
  SQUARE_TYPE E = SQUARE_TYPE::EMPTY;
  SQUARE_TYPE G = SQUARE_TYPE::GOAL;
  SQUARE_TYPE S = SQUARE_TYPE::START;

  std::vector<std::vector<SQUARE_TYPE>> board = {{W, W, W, W, W, W, W, W},
                                                 {W, E, E, E, E, E, E, W},
                                                 {W, E, W, W, W, W, W, W},
                                                 {W, E, W, W, E, W, W, W},
                                                 {W, E, W, W, E, W, W, W},
                                                 {W, E, W, W, E, E, E, W},
                                                 {W, E, W, W, E, W, E, W},
                                                 {W, E, E, W, S, W, E, W},
                                                 {W, W, E, W, E, W, E, W},
                                                 {W, E, E, E, E, W, E, W},
                                                 {W, W, E, W, W, W, W, W},
                                                 {W, E, E, E, E, E, E, W},
                                                 {W, W, E, W, W, W, G, W},
                                                 {W, W, W, W, W, W, W, W}

  };

  Maze tab;
  Bot bot;
  // bot.solve<ALGORITHM::BFS>(tab);
  // bot.solve<ALGORITHM::DFS>(tab);
  // bot.solve<ALGORITHM::A_STAR>(tab);
  bot.solve<ALGORITHM::A_STAR>(tab);
  tab.paintPath(bot.getSolution(), bot.getSearchedPath());
  tab.printMaze();
  // for (const auto &sq : bot.getSearchedPath()) {
  //   std::cout << static_cast<int>(sq.first) << "  "
  //             << static_cast<int>(sq.second) << std::endl;
  // }
}
