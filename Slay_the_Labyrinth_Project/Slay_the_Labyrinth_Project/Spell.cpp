#include "Spell.h"
#include "BattleManager.h"
#include "Player.h"
#include "Enemy.h"

Spell::Spell(std::string name, int cur_dur, int max_dur, int cost) : m_name(name),
	m_CurDur(cur_dur),
	m_MaxDur(max_dur),
	m_cost(cost) {}

std::vector<Spell> Spell::GetSpells(std::string className, DataManager& dm) {
	if (className.size() == 5)       return WarriorSpells(dm);
	else if (className.size() == 10) return RogueSpells(dm);
	else                              return MageSpells(dm);
}

std::vector<Spell> Spell::WarriorSpells(DataManager& dm) {
	return {
		Spell(dm.GetSpellName("rage"), 0, 3, 30),
		Spell(dm.GetSpellName("sweeping_strike"), 0, 0, 20),
		Spell(dm.GetSpellName("regeneration_potion"), 0, 3, 30)
	};
}

std::vector<Spell> Spell::RogueSpells(DataManager& dm) {
	return {
		Spell(dm.GetSpellName("backstab"), 0, 0, 18),
		Spell(dm.GetSpellName("speed_potion"), 0, 3, 30),
		Spell(dm.GetSpellName("dust_in_eyes"), 0, 3, 30)
	};
}

std::vector<Spell> Spell::MageSpells(DataManager& dm) {
	return {
		Spell(dm.GetSpellName("fireball"), 0, 0, 30),
		Spell(dm.GetSpellName("frost_vortex"), 0, 3, 30),
		Spell(dm.GetSpellName("healing"), 0, 0, 20)
	};
}

int Spell::Rage(Player* player) {
	return { player->GetATK() * 2 -  20};
}
int Spell::Sweeping_strike(int intell) {
	return 20 + (intell / 2);
}
int Spell::Regeneration_potion() {
	return 15;
}
int Spell::Backstab(int intell) {
	return 15 + (intell / 2);
}
int Spell::Speed_potion(Player* player) {
	return { player->GetSPD() * 2 - 20};
}
int Spell::Dust_in_eyes(Enemy* enemy) {
	return ( enemy->GetATK() / 2);
}
int Spell::Fireball(int intell){
	return 30 + (intell / 2);
}
int Spell::Frost_vortex(Enemy* enemy) {
	return { enemy->GetSPD() / 2};
}
int Spell::Healing(int intell) {
	return 15 + (intell / 2);
}