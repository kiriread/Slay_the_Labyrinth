#pragma once
#include <string>
#include <vector>

#include "Stats.h"
#include "DataManager.h"

class Enemy {
 private:
  std::string m_name;
  Stats m_stats;
  int m_originalSPD;

 public:
  Enemy(std::string name, int hp, int atk, int spd);

  // Геттеры
  std::string GetName() const { return m_name; }
  int GetCurrentHP() const { return m_stats.CurrentHP; }
  int GetMaxHP() const { return m_stats.MaxHP; }
  int GetATK() const { return m_stats.ATK; }
  int GetSPD() const { return m_stats.SPD; }

  // Боевка
  void TakeDamage(int amount);
  bool IsDead() const { return m_stats.CurrentHP <= 0; }

  void SetSPD(int spd);
  void RestoreSPD();
};

// Вектора врагов
std::vector<Enemy> RegularEnemy(DataManager& dataManager);
std::vector<Enemy> EliteEnemy(DataManager& dataManager);
std::vector<Enemy> Bosses(DataManager& dataManager);
