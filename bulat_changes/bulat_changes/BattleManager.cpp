#include "BattleManager.h"
#include "EnemyCreator.h"
#include "Enemy.h"
#include "Stats.h"
#include "Player.h"

void BattleManager::StartBattle(RoomType room) {
	EnemyCreator enemyCreator;
	enemy = enemyCreator.OnEnterB(room);
	player.CurrentHP = obj.GetCurrentHP();
	player.CurrentMP = obj.GetCurrentMP();
	player.ATK = obj.GetATK();
	player.INT = obj.GetINT();
	player.SPD = obj.GetSPD();
	p_Initiative = int(BattleVariants::START_INITIATIVE);
	e_Initiative = int(BattleVariants::START_INITIATIVE);
}
void BattleManager::StartTurn(Enemy enemy, Stats player) {
	while (true) {
		CalculateInitiative(e_Initiative, p_Initiative);
		if (is_p_turn) {
			PlayerTurn();
		}
		else {
			EnemyTurn();
		}
	}
}
void BattleManager::CalculateInitiative(int e_Initiative, int p_Initiative) {
	if ((int(BattleVariants::TURN) - p_Initiative) / player.SPD <= (int(BattleVariants::TURN) - e_Initiative) / enemy.SPD) {
		is_p_turn = true;
		p_Initiative = int(BattleVariants::START_INITIATIVE);
		e_Initiative = enemy.SPD * ((int(BattleVariants::TURN) - p_Initiative) / player.SPD);
	}
	else {
		is_p_turn = false;
		e_Initiative = int(BattleVariants::START_INITIATIVE);
		p_Initiative = player.SPD * ((int(BattleVariants::TURN) - e_Initiative) / enemy.SPD);
	}
}
void PlayerTurn() {

}
void EnemyTurn() {

}