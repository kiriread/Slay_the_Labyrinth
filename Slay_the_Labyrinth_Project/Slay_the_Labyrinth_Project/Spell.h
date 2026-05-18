#pragma once
#include <string>
#include "DataManager.h"
#include "Player.h"
#include "Enemy.h"

class Spell {
private:
	std::string m_name;
	int m_CurDur;
	int m_MaxDur;
	int m_cost;

	DataManager m_dataManager;
public:
	Spell(std::string name, int cur_dur, int max_dur, int cost);

	std::string GetName() const { return m_name; }
	int GetCurDur() const { return m_CurDur; }
	int GetMaxDur() const { return m_MaxDur; }
	int GetCost() const { return m_cost; }

	std::vector<Spell> GetSpells(std::string class_name);

	int Rage(Player* player);
	int Sweeping_strike();
	int Regeneration_potion();
	int Backstab();
	int Speed_potion(Player* player);
	int Dust_in_eyes(Enemy* enemy);
	int Fireball();
	int Frost_vortex(Enemy* enemy);
	int Healing();

	std::vector<Spell> WarriorSpells();
	std::vector<Spell> RogueSpells();
	std::vector<Spell> MageSpells();
};