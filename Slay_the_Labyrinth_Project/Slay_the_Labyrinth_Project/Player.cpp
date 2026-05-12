#include "Player.h"

Player::Player(std::string className, Stats stats)
    : m_className(className)
    , m_stats(stats)
{
    stats.CurrentHP = stats.MaxHP;
    stats.CurrentMP = stats.MaxMP;
}

void Player::RestoreHP(int amount) {
    m_stats.CurrentHP += amount;
    if (m_stats.CurrentHP > GetMaxHP())
        m_stats.CurrentHP = GetMaxHP();
}

void Player::RestoreMP(int amount) {
    m_stats.CurrentMP += amount;
    if (m_stats.CurrentMP > GetMaxMP())
        m_stats.CurrentMP = GetMaxMP();
}

int Player::GetGold() const {
    return m_gold;
}

void Player::AddGold(int amount) {
    m_gold += amount;
}

// Потратить золото. Возвращает false, если не хватает
bool Player::SpendGold(int amount) {
    if (m_gold < amount) {
        return false;  
    }
    m_gold -= amount;
    return true;
}

void Player::AddArtifact(const std::string& id) {
    m_inventory.push_back(id);
}

// Получить список ID артефактов (только для чтения)
const std::vector<std::string>& Player::GetInventory() const {
    return m_inventory;
}