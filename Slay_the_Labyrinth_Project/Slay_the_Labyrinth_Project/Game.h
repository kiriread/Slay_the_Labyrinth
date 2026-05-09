#pragma once

#include "Player.h"
#include "DataManager.h"
#include "ConsoleUtils.h"
#include "Stats.h"

class Game {
private:
	bool m_isRunning;
	std::string m_className;
	Player* m_player;
	DataManager m_dataManager;
	ConsoleUtils m_console;
	Stats m_stats;

	void ShowMainMenu();
	void Render();
	void ProcessInput(int key);

public:
	Game();
	~Game();
	void Run();
};