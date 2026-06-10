#include "Spell.h"
#include "BattleManager.h"
#include "Player.h"
#include "Enemy.h"

Spell::Spell(std::string name, int cur_dur, int max_dur, int cost) : m_name(name),
	m_CurDur(cur_dur),
	m_MaxDur(max_dur),
	m_cost(cost)
{
	m_dataManager.LoadSpells("assets/json/spells.json");
}

std::vector<Spell> Spell::GetSpells(std::string class_name) {
	std::vector<Spell> spells;
	for (int i = 0; i < 3; i++) {
		if (class_name.size() == 5) {
			return WarriorSpells();
		}
		else if (class_name.size() == 10) {
			return RogueSpells();
		}
		else {
			return MageSpells();
		}
	}
}
std::vector<Spell> Spell::WarriorSpells() {
	return { Spell(m_dataManager.GetSpellName("rage"), 0, 3, 30), Spell(m_dataManager.GetSpellName("sweeping_strike"), 0, 0, 20),
		Spell(m_dataManager.GetSpellName("regeneration_potion"), 0, 3, 30)};
}
std::vector<Spell> Spell::RogueSpells() {

	return { Spell(m_dataManager.GetSpellName("backstab"), 0, 0, 18), Spell(m_dataManager.GetSpellName("speed_potion"), 0, 3, 30),
		Spell(m_dataManager.GetSpellName("dust_in_eyes"), 0, 3, 30) };
}
std::vector<Spell> Spell::MageSpells() {
	return { Spell(m_dataManager.GetSpellName("fireball"), 0, 0, 30), Spell(m_dataManager.GetSpellName("frost_vortex"), 0, 3, 30),
		Spell(m_dataManager.GetSpellName("healing"), 0, 0, 20) };
}

int Spell::Rage(Player* player) {
	return { player->GetATK() * 2 -  20};
}
int Spell::Sweeping_strike(int intell) {
	return 20 + (intell / 2);
}
int Spell::Regeneration_potion() {
	return 0;
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
int Spell::Healing() {
	return 15;
}