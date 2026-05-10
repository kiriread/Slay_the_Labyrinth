#pragma once

#include "Room.h"

class EliteRoom : public Room {
public:
	EliteRoom();
	void OnEnter(Player* player) override;
};
