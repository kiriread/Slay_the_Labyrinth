#include "BossRoom.h"

#include "BattleManager.h"

BossRoom::BossRoom(Game* game) 
	: Room(RoomType::BOSS)
	, m_game(game){}

void BossRoom::OnEnter(Player* player) {
  BattleManager bm(player, m_game);
  bm.StartBattle(RoomType::BOSS);
  m_resultText = "Победа!";
}
