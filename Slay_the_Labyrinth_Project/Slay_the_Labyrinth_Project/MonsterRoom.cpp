#include "MonsterRoom.h"

MonsterRoom::MonsterRoom(Game* game) 
	: Room(RoomType::MONSTER)
	, m_game(game)
	, m_dataManager() {
	m_dataManager.LoadStrings("assets/json/strings.json");
}

void MonsterRoom::OnEnter(Player* player) {
  m_resultText = m_dataManager.GetString("mon_win");
  BattleManager bm(player, m_game);
  bm.StartBattle(RoomType::MONSTER);
}
