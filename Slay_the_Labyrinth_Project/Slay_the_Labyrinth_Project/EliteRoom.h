#pragma once

#include "Room.h"
#include "BattleManager.h"

class EliteRoom : public Room {
private:
	Game* m_game;
public:
	EliteRoom(Game* game);
	void OnEnter(Player* player) override;
};
