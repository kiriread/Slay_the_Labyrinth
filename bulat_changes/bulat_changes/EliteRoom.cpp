#include "EliteRoom.h"
#include "BattleManager.h"

EliteRoom::EliteRoom() : Room(RoomType::REST) {
    m_description = "";
}

void EliteRoom::OnEnter(Player* player) {
    BattleManager obj;
    obj.StartBattle(RoomType::ELITE);
}