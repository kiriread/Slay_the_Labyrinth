#include "EliteRoom.h"

EliteRoom::EliteRoom(Game* game) : Room(RoomType::ELITE), m_game(game) {}

void EliteRoom::OnEnter(Player* player) {
  m_resultText = "dsfsdf, 2 sdfsfs";
  BattleManager bm(player, m_game);
  bm.StartBattle(RoomType::ELITE);
}
