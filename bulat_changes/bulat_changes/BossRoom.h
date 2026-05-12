#pragma once

#include "Room.h"

class BossRoom : public Room {
public:
	BossRoom();
	void OnEnter(Player* player) override;
};
