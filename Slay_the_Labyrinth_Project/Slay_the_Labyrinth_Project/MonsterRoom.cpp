#include "MonsterRoom.h"

MonsterRoom::MonsterRoom(Game* game) 
	: Room(RoomType::MONSTER)
	, m_game(game){}

void MonsterRoom::OnEnter(Player* player) {
  m_resultText = "Получено X золота, 1 артефакт";
  BattleManager bm(player, m_game);
  bm.StartBattle(RoomType::MONSTER);
}
