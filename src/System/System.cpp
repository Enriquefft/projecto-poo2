#include "System.hpp"
#include "../Board/Board.hpp"
#include "../Bot/Bot.hpp"

void System::run() {
  // m_vista.startScreen();
  Board tab;
  Bot bot;
  bot.solve<ALGORITHM::BFS>(tab);
  tab.paintPath(bot.getSolution(), bot.getSearchedPath());
  tab.printBoard();
}
