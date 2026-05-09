#include "Player.h"

Player::Player(std::string className, Stats stats)
    : m_className(className)
    , m_stats(stats)
{
    stats.CurrentHP = stats.MaxHP;
    stats.CurrentMP = stats.MaxMP;
}