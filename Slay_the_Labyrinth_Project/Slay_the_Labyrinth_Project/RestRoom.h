#pragma once

#include "Room.h"

class RestRoom : public Room {
public:
	RestRoom();
	void OnEnter(Player* player) override;
};