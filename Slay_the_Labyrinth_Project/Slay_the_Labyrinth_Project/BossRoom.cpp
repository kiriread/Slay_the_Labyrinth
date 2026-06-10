#include "BossRoom.h"

#include "BattleManager.h"

BossRoom::BossRoom(Game* game, DataManager* dm, ConsoleUtils* co)
	: Room(RoomType::BOSS)
	, m_game(game)
	, m_dataManager(dm)
	, m_console(co){}

void BossRoom::OnEnter(Player* player) {
  BattleManager bm(player, m_game, m_dataManager, m_console);
  bm.StartBattle(RoomType::BOSS);
}
