#include "Spell.h"
#include "BattleManager.h"
#include "Player.h"
#include "Enemy.h"

Spell::Spell(std::string name, int cur_dur, int max_dur, int cost) : m_name(name),
	m_CurDur(cur_dur),
	m_MaxDur(max_dur),
	m_cost(cost)
{
}

std::vector<Spell> Spell::GetSpells(std::string class_name) {
	std::vector<Spell> spells;
	for (int i = 0; i < 3; i++) {
		if (class_name == "warrior") {
			return WarriorSpells();
		}
		else if (class_name == "rogue") {
			return RogueSpells();
		}
		else {
			return MageSpells();
		}
	}
}
std::vector<Spell> Spell::WarriorSpells() {
	return { Spell("Rage", 0, 3, 30), Spell("Sweeping strike", 0, 0, 20), 
		Spell("Regeneration potion", 0, 3, 30)};
}
std::vector<Spell> Spell::RogueSpells() {
	return { Spell("Backstab", 0, 0, 18), Spell("Speed potion", 0, 3, 30),
		Spell("Dust in eyes", 0, 3, 30) };
}
std::vector<Spell> Spell::MageSpells() {
	return { Spell("Fireball", 0, 0, 30), Spell("Frost vortex", 0, 3, 30),
		Spell("Healing", 0, 0, 20) };
}

int Spell::Rage(Player* player) {
	return { player->GetATK() * 2 };
}
int Spell::Sweeping_strike() {
	return 40;
}
int Spell::Regeneration_potion() {
	return 0;
}
int Spell::Backstab() {
	return 35;
}
int Spell::Speed_potion(Player* player) {
	return { player->GetSPD() * 2};
}
int Spell::Dust_in_eyes(Enemy* enemy) {
	return ( enemy->GetATK() / 2);
}
int Spell::Fireball(){
	return 50;
}
int Spell::Frost_vortex(Enemy* enemy) {
	return { enemy->GetSPD() / 2};
}
int Spell::Healing() {
	return 15;
}