#include "EliteRoom.h"

EliteRoom::EliteRoom(Game* game, DataManager* dm, ConsoleUtils* co) : Room(RoomType::ELITE), m_game(game), m_dataManager(dm), m_console(co) {
}

void EliteRoom::OnEnter(Player* player) {
  m_resultText = m_dataManager->GetString("el_win");
  BattleManager bm(player, m_game, m_dataManager, m_console);
  bm.StartBattle(RoomType::ELITE);
}
