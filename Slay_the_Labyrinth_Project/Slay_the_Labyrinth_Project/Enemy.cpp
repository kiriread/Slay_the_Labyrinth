#include "Enemy.h"

Enemy::Enemy(std::string name, int hp, int atk, int spd) : m_name(name) {
  m_stats.MaxHP = hp;
  m_stats.CurrentHP = hp;
  m_stats.ATK = atk;
  m_stats.SPD = spd;
}

void Enemy::TakeDamage(int amount) {
  m_stats.CurrentHP -= amount;
  if (m_stats.CurrentHP < 0) m_stats.CurrentHP = 0;
}

void Enemy::SetSPD(int spd) {
  m_stats.SPD = spd;
  if (m_stats.SPD < 0) m_stats.SPD = 0;
}

void Enemy::RestoreSPD() { m_stats.SPD = m_originalSPD; }

std::vector<Enemy> RegularEnemy(DataManager& dataManager) {
  return {Enemy(dataManager.GetString("goblin"), 35, 15, 10),
          Enemy(dataManager.GetString("skeleton"), 50, 15, 10),
          Enemy(dataManager.GetString("slime"), 60, 17, 15)};
}

std::vector<Enemy> EliteEnemy(DataManager& dataManager) {
  return {Enemy(dataManager.GetString("troll"), 50, 25, 25),
          Enemy(dataManager.GetString("ogre"), 70, 20, 25)};
}

std::vector<Enemy> Bosses(DataManager& dataManager) {
  return {Enemy(dataManager.GetString("dragon"), 90, 20, 40),
          Enemy(dataManager.GetString("succub"), 70, 15, 40)};
}
