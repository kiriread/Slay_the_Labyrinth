#include "MonsterRoom.h"

MonsterRoom::MonsterRoom() : Room(RoomType::REST) {
    m_description = "";
}

void MonsterRoom::OnEnter(Player* player) {

}