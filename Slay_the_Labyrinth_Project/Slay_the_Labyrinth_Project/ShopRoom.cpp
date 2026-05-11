#include "ShopRoom.h"

ShopRoom::ShopRoom() : Room(RoomType::REST) {}

void ShopRoom::OnEnter(Player* player) {
	m_resultText = "Куплено";
}
