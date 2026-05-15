#pragma once

#include "Room.h"
#include "ConsoleUtils.h"
#include "DataManager.h"

class Game;

class RestRoom : public Room {
 private:
  DataManager* m_dataManager;
  ConsoleUtils* m_console;
  Game* m_game;

 public:
  RestRoom(DataManager* dm, ConsoleUtils* console, Game* game);
  void OnEnter(Player* player) override;
};
