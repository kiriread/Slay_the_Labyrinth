#include "EliteRoom.h"

EliteRoom::EliteRoom(Game* game) : Room(RoomType::ELITE), m_game(game) {
	m_dataManager.LoadStrings("assets/json/strings.json");
}

void EliteRoom::OnEnter(Player* player) {
  m_resultText = m_dataManager.GetString("el_win");
  BattleManager bm(player, m_game);
  bm.StartBattle(RoomType::ELITE);
}
