#pragma once
#include "Enemy.h"
#include "Room.h"
#include "EnemyCreator.h"
#include "Stats.h"
#include "Player.h"

enum class BattleVariants {TURN = 10, START_INITIATIVE = 0};

class BattleManager {
	private:
		Enemy enemy{};
		Player obj{};
		Stats player{};
		int p_Initiative = 0;
		int e_Initiative = 0;
		bool is_p_turn = true;
	public:
		void StartBattle(RoomType room);
		void StartTurn(Enemy enemy, Stats player);
		void CalculateInitiative(int e_SPD, int p_SPD);
};