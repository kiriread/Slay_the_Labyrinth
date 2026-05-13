#pragma once
#include <variant>
#include "Room.h"

enum class enemyVariants {NAME = 1, HP = 2, ATK = 3, SPD = 4};

class EnemyCreator {
	public:
		Enemy OnEnterB(RoomType type);
};
