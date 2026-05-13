#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Room.h"
#include "DataManager.h"
#include "ConsoleUtils.h"
#include "Game.h"

class BattleManager {
 private:
  Player* m_player;
  Enemy* m_enemy;
  Game* m_game;
  int m_pInitiative;
  int m_eInitiative;
  bool m_isPlayerTurn;
  DataManager m_dataManager;
  ConsoleUtils m_console;

  void PlayerTurn();
  void EnemyTurn();

 public:
  BattleManager(Player* player, Game* game);
  ~BattleManager();
  void StartBattle(RoomType room);
  void CalculateInitiative();
  void EnemyHUD();
};
