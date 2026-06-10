#include "MonsterRoom.h"

MonsterRoom::MonsterRoom(Game* game, DataManager* dm, ConsoleUtils* co)
	: Room(RoomType::MONSTER)
	, m_game(game)
	, m_dataManager(dm)
	, m_console(co)
{
}

void MonsterRoom::OnEnter(Player* player) {
  m_resultText = m_dataManager->GetString("mon_win");
  BattleManager bm(player, m_game, m_dataManager, m_console);
  bm.StartBattle(RoomType::MONSTER);
}
