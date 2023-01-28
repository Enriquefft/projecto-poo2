#include "System.hpp"
#include "../Board/Board.hpp"
#include "../Bot/Bot.hpp"

void System::run() {
  // m_vista.startScreen();
  Board tab;
  tab.printBoard();
  Bot bot;
  bot.solve<ALGORITHM::BFS>(tab);
}
