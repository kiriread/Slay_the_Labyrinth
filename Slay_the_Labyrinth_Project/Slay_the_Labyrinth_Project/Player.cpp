#include "Player.h"

Player::Player(std::string className, Stats stats)
    : className(className)
    , stats(stats)
{
    stats.CurrentHP = stats.MaxHP;
    stats.CurrentMP = stats.MaxMP;
}