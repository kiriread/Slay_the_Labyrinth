#include "EliteRoom.h"

EliteRoom::EliteRoom() : Room(RoomType::REST) {}

void EliteRoom::OnEnter(Player* player) {
	m_resultText = "Получено X золота, 2 артефакта";
}