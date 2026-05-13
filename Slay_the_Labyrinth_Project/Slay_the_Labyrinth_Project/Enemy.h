#pragma once
#include <string>
#include <vector>
#include "Stats.h"

class Enemy {
private:
    std::string m_name;
    Stats m_stats;

public:
    Enemy(std::string name, int hp, int atk, int spd);

    // Getters
    std::string GetName() const { return m_name; }
    int GetCurrentHP() const { return m_stats.CurrentHP; }
    int GetMaxHP() const { return m_stats.MaxHP; }
    int GetATK() const { return m_stats.ATK; }
    int GetSPD() const { return m_stats.SPD; }

    // Combat
    void TakeDamage(int amount);
    bool IsDead() const { return m_stats.CurrentHP <= 0; }
};

// Factory functions
std::vector<Enemy> RegularEnemy();
std::vector<Enemy> EliteEnemy();
std::vector<Enemy> Bosses();