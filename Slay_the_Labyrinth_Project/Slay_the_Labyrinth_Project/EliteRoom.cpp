#include "EliteRoom.h"

EliteRoom::EliteRoom() : Room(RoomType::ELITE) {}

void EliteRoom::OnEnter(Player* player) {
	m_resultText = "Получено X золота, 2 артефакта";
	BattleManager bm(player);
	bm.StartBattle(RoomType::ELITE);
}