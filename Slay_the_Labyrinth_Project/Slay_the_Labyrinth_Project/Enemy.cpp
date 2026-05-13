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

std::vector<Enemy> RegularEnemy() {
  return {Enemy("Призрак", 30, 20, 50), Enemy("Орк с дубиной", 50, 15, 30),
          Enemy("Слизень", 60, 16, 20)};
}

std::vector<Enemy> EliteEnemy() {
  return {Enemy("аываолль шаман", 50, 40, 50), Enemy("Огр маг", 70, 30, 30)};
}

std::vector<Enemy> Bosses() {
  return {Enemy("Чёрный дракон", 90, 50, 50), Enemy("Демон крови", 70, 30, 80)};
}
