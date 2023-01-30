#include "System.hpp"
#include "../Bot/Bot.hpp"
#include "../Maze/Maze.hpp"

void System::run() {
  // m_vista.startScreen();
  Maze tab;
  Bot bot;
  bot.solve<ALGORITHM::BFS>(tab);
  bot.solve<ALGORITHM::DFS>(tab);
  bot.solve<ALGORITHM::A_STAR>(tab);
  bot.solve<ALGORITHM::GBGS>(tab);
  tab.paintPath(bot.getSolution(), bot.getSearchedPath());
  tab.printMaze();
}
