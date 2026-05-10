#pragma once

#include "Room.h"

class ShopRoom : public Room {
public:
	ShopRoom();
	void OnEnter(Player* player) override;
};
