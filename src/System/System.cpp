#include "System.hpp"
#include "../Board/Board.hpp"
#include "../Bot/Bot.hpp"

void System::run() {
  // m_vista.startScreen();
  Board tab;
  Bot bot;
  bot.solve<ALGORITHM::BFS>(tab);
  bot.solve<ALGORITHM::DFS>(tab);
  bot.solve<ALGORITHM::A_STAR>(tab);
  bot.solve<ALGORITHM::GBGS>(tab);
  tab.paintPath(bot.getSolution(), bot.getSearchedPath());
  tab.printBoard();
}
