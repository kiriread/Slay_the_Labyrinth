#pragma once

#include "Room.h"
#include "BattleManager.h"

class MonsterRoom : public Room {
public:
	MonsterRoom();
	void OnEnter(Player* player) override;
};