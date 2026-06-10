#pragma once

#include "Room.h"
#include "BattleManager.h"
#include "DataManager.h"

class EliteRoom : public Room {
private:
	DataManager m_dataManager;
	Game* m_game;
public:
	EliteRoom(Game* game);
	void OnEnter(Player* player) override;
};
