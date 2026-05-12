#include "BossRoom.h"
#include "BattleManager.h"

BossRoom::BossRoom() : Room(RoomType::REST) {
    m_description = "";
}

void BossRoom::OnEnter(Player* player) {
    BattleManager obj;
    obj.StartBattle(RoomType::BOSS);
}