#pragma once

#include "Room.h"
#include "BattleManager.h"

class BossRoom : public Room {
public:
	BossRoom();
	void OnEnter(Player* player) override;
};
