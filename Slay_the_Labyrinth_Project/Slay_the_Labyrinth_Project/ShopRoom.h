#pragma once
#include <string>
#include <vector>

#include "ConsoleUtils.h"
#include "DataManager.h"
#include "Room.h"

class Game;

class ShopRoom : public Room {
 private:
  std::vector<std::string> m_stock;
  DataManager* m_dataManager;
  ConsoleUtils* m_console;
  Game* m_game;

 public:
  ShopRoom(DataManager* dm, ConsoleUtils* console, Game* game);
  void OnEnter(Player* player) override;
};
