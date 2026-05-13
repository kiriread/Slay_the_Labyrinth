#include "MonsterRoom.h"

MonsterRoom::MonsterRoom(Game* game) 
	: Room(RoomType::MONSTER)
	, m_game(game){}

void MonsterRoom::OnEnter(Player* player) {
  m_resultText = "Тут бяка xddd";
  BattleManager bm(player, m_game);
  bm.StartBattle(RoomType::MONSTER);
}
