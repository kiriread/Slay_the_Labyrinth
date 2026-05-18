#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Room.h"
#include "DataManager.h"
#include "ConsoleUtils.h"
#include "Game.h"
#include "Spell.h"

class BattleManager {
 private:
  Player* m_player;
  Enemy* m_enemy;
  Game* m_game;
  Spell m_sp;
  int m_pInitiative;
  int m_eInitiative;
  bool m_isPlayerTurn;
  int m_totalATK;
  int m_totalSPD;
  int m_totalEnemyATK;
  int m_totalEnemySPD;
  int m_rage_dur;
  int m_regen_dur;
  int m_spdPotion_dur;
  int m_dusk_dur;
  int m_frost_dur;
  std::vector<Spell> m_spells;
  DataManager m_dataManager;
  ConsoleUtils m_console;

  void PlayerTurn();
  void SpellChoice();
  void EnemyTurn();

 public:
  BattleManager(Player* player, Game* game);
  ~BattleManager();
  void StartBattle(RoomType room);
  void CalculateInitiative();
  void EnemyHUD();
};
