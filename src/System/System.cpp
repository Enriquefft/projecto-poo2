#include "System.hpp"
#include "../Board/Board.hpp"
#include "../Bot/Bot.hpp"

void System::run() {
  // m_vista.startScreen();
  Board tab;
  tab.printBoard();
  Bot bot;
  bot.solve<ALGORITHM::DFS>(tab);
  for (const auto &move : bot.getSolution()) {
    std::cout << static_cast<int>(move.first) << '\t'
              << static_cast<int>(move.second) << std::endl;
  }
  tab.paintPath(bot.getSolution(), bot.getSearchedPath());
  tab.printBoard();
  // for (const auto &move : bot.getSearchedPath()) {
  //   std::cout << static_cast<int>(move.first) << '\t'
  //             << static_cast<int>(move.second) << std::endl;
  // }
}
