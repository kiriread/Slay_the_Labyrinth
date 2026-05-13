#pragma once

#include "Room.h"
#include "BattleManager.h"

class BossRoom : public Room {
private:
	Game* m_game;
public:
	BossRoom(Game* game);
	void OnEnter(Player* player) override;
};
