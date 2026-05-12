#include "MonsterRoom.h"

MonsterRoom::MonsterRoom() : Room(RoomType::MONSTER) {}

void MonsterRoom::OnEnter(Player* player) {
  m_resultText = "Получено X золота, 1 артефакт";
  BattleManager bm(player);
  bm.StartBattle(RoomType::MONSTER);
}
