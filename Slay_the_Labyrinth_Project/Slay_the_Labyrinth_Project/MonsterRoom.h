#pragma once

#include "Room.h"
#include "BattleManager.h"

class MonsterRoom : public Room {
private:
	Game* m_game;
public:
	MonsterRoom(Game* game);
	void OnEnter(Player* player) override;
};