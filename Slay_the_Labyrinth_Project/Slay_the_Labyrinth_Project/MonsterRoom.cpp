#include "MonsterRoom.h"

MonsterRoom::MonsterRoom() : Room(RoomType::REST) {}

void MonsterRoom::OnEnter(Player* player) {
  m_resultText = "Получено X золота, 1 артефакт";
}
