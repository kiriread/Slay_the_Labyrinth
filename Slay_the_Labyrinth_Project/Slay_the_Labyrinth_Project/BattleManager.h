#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Room.h"

class BattleManager {
 private:
  Player* m_player;
  Enemy* m_enemy;
  int m_pInitiative;
  int m_eInitiative;
  bool m_isPlayerTurn;

  void PlayerTurn();
  void EnemyTurn();

 public:
  BattleManager(Player* player);
  ~BattleManager();
  void StartBattle(RoomType room);
  void CalculateInitiative();
};
