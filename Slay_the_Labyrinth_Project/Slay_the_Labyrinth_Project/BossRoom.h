#pragma once

#include "Room.h"
#include "BattleManager.h"
#include "ConsoleUtils.h"

class Game;

class BossRoom : public Room {
private:
	Game* m_game;
	DataManager* m_dataManager;
	ConsoleUtils* m_console;
public:
	BossRoom(Game* game, DataManager* dm, ConsoleUtils* co);
	void OnEnter(Player* player) override;
};
