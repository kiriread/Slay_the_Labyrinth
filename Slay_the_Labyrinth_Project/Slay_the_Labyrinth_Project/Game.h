#pragma once

#include "ConsoleUtils.h"
#include "DataManager.h"
#include "MapGenerator.h"
#include "Player.h"
#include "Room.h"
#include "Stats.h"

#include "RestRoom.h"
#include "ShopRoom.h"
#include "MonsterRoom.h"
#include "EliteRoom.h"
#include "BossRoom.h"

class Game {
 private:
  bool m_isRunning;
  std::string m_className;
  Player* m_player;
  DataManager m_dataManager;
  ConsoleUtils m_console;
  Stats m_stats;
  int m_currentCount;
  std::vector<RoomType> m_roomOptions;
  MapGenerator m_mapGenerator;

  void MainMenu();
  /*void YourChoice();*/
  /*void ProcessInput(int key);*/
  void RoomChoice();
  void EnterRoom(RoomType type); 

 public:
  Game();
  ~Game();
  void Run();
  void HUD(int x);
};
