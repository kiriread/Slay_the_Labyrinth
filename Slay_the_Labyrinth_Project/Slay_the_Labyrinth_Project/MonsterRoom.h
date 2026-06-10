#pragma once

#include "Room.h"
#include "BattleManager.h"
#include "DataManager.h"

class MonsterRoom : public Room {
private:
	DataManager m_dataManager;
	Game* m_game;
public:
	MonsterRoom(Game* game);
	void OnEnter(Player* player) override;
};