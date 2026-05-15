#include "Player.h"

Player::Player(std::string classId, std::string className, Stats stats)
    : m_classId(classId), m_className(className), m_stats(stats) {
  stats.CurrentHP = stats.MaxHP;
  stats.CurrentMP = stats.MaxMP;
}

void Player::RestoreHP(int amount) {
  m_stats.CurrentHP += amount;
  if (m_stats.CurrentHP > GetMaxHP()) m_stats.CurrentHP = GetMaxHP();
}

void Player::RestoreMP(int amount) {
  m_stats.CurrentMP += amount;
  if (m_stats.CurrentMP > GetMaxMP()) m_stats.CurrentMP = GetMaxMP();
}

int Player::GetGold() const { return m_gold; }

void Player::AddGold(int amount) { m_gold += amount; }

// Потратить золото. Возвращает false, если не хватает
bool Player::SpendGold(int amount) {
  if (m_gold < amount) {
    return false;
  }
  m_gold -= amount;
  return true;
}

// Получить список ID артефактов (только для чтения)
const std::vector<std::string>& Player::GetInventory() const {
  return m_inventory;
}

void Player::AddArtifact(const std::string& id) {
  m_inventory.push_back(id);

  // Статы
  if (id == "whetstone") m_stats.BonusATK += 5;
  if (id == "speed_boots") m_stats.BonusSPD += 5;
  if (id == "banana") m_stats.BonusMaxHP += 10;
  if (id == "pear") m_stats.BonusMaxHP += 5;
  if (id == "ancient_tome") m_stats.BonusINT += 5;
  if (id == "magic_stone") m_stats.BonusMaxMP += 15;
  if (id == "magic_boulder") m_stats.BonusMaxMP += 25;
  if (id == "berserk_talisman") {
    m_stats.BonusATK += 3;
    m_stats.BonusSPD += 3;
  }

  // Пассивные (не статы) — healing_sprout, diadem, sleep_pillow, sleep_blanket,
  // sleeping_pill, humidifier, clover_petal, discount_coupon, trial_amulet,
  // perfection_armor, revival_amulet
  // Эти эффекты проверяются в других местах
}
