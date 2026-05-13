ï»¿#include "MonsterRoom.h"

MonsterRoom::MonsterRoom(Game* game) 
	: Room(RoomType::MONSTER)
	, m_game(game){}

void MonsterRoom::OnEnter(Player* player) {
  m_resultText = "ÐÐ¾Ð»ÑÑÐµÐ½Ð¾ X Ð·Ð¾Ð»Ð¾ÑÐ°, 1 Ð°ÑÑÐµÑÐ°ÐºÑ";
  BattleManager bm(player, m_game);
  bm.StartBattle(RoomType::MONSTER);
}
