#include "ShopRoom.h"

ShopRoom::ShopRoom() : Room(RoomType::SHOP) {}

void ShopRoom::OnEnter(Player* player) {
	m_resultText = "Куплено";
}
