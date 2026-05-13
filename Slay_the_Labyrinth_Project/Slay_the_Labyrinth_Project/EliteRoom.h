#pragma once

#include "Room.h"
#include "BattleManager.h"

class EliteRoom : public Room {
public:
	EliteRoom();
	void OnEnter(Player* player) override;
};
