#include "BossRoom.h"

BossRoom::BossRoom() : Room(RoomType::REST) {}

void BossRoom::OnEnter(Player* player) {
	m_resultText = "Победа!";
}