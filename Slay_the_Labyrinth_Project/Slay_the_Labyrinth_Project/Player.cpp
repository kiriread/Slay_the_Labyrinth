#include "Player.h"

Player::Player(std::string className, Stats stats) 
{
    this->className = className;
    this->stats = stats;
    this->stats.CurrentHP = this->stats.MaxHP;
    this->stats.CurrentMP = this->stats.MaxMP;
}