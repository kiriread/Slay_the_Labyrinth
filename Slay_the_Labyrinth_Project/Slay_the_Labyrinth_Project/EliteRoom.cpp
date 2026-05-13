#include "EliteRoom.h"

EliteRoom::EliteRoom(Game* game) 
	: Room(RoomType::ELITE)
	, m_game(game){}

void EliteRoom::OnEnter(Player* player) {
	m_resultText = "ÐÐ¾Ð»ÑÑÐµÐ½Ð¾ X Ð·Ð¾Ð»Ð¾ÑÐ°, 2 Ð°ÑÑÐµÑÐ°ÐºÑÐ°";
	BattleManager bm(player, m_game);
	bm.StartBattle(RoomType::ELITE);
}