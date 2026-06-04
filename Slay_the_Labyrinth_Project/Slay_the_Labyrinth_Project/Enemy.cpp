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
  return {Enemy("ÐÑÐ¸Ð·ÑÐ°Ðº", 30, 20, 50), Enemy("ÐÑÐº Ñ Ð´ÑÐ±Ð¸Ð½Ð¾Ð¹", 50, 15, 30),
          Enemy("Ð¡Ð»Ð¸Ð·ÐµÐ½Ñ", 60, 16, 20)};
}

std::vector<Enemy> EliteEnemy() {
  return {Enemy("Ð°ÑÐ²Ð°Ð¾Ð»Ð»Ñ ÑÐ°Ð¼Ð°Ð½", 50, 40, 50), Enemy("ÐÐ³Ñ Ð¼Ð°Ð³", 70, 30, 30)};
}

std::vector<Enemy> Bosses() {
  return {Enemy("Чёрный дракон", 90, 20, 50), Enemy("Суккуб", 70, 30, 60)};
}
