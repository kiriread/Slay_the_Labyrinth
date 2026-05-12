#include "MonsterRoom.h"
#include "BattleManager.h"

MonsterRoom::MonsterRoom() : Room(RoomType::REST) {
    m_description = "";
}

void MonsterRoom::OnEnter(Player* player) {
    BattleManager obj;
    obj.StartBattle(RoomType::MONSTER);
}