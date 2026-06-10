#pragma once

#include "Room.h"
#include "BattleManager.h"
#include "DataManager.h"
#include "ConsoleUtils.h"

class Game;

class MonsterRoom : public Room {
private:
	DataManager* m_dataManager;
	Game* m_game;
	ConsoleUtils* m_console;
public:
	MonsterRoom(Game* game, DataManager* dm, ConsoleUtils* co);
	void OnEnter(Player* player) override;
};