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