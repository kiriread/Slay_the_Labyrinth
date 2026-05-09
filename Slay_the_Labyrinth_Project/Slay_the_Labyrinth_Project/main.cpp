#include <windows.h>

#include "Game.h"

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  Game game;
  game.Run();

  return 0;
}
