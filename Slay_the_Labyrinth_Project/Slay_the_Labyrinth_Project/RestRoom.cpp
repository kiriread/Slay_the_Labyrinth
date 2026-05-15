#include "RestRoom.h"

#include "Game.h"
#include "Player.h"

RestRoom::RestRoom(DataManager* dm, ConsoleUtils* console, Game* game)
    : Room(RoomType::REST),
      m_dataManager(dm),
      m_console(console),
      m_game(game) {}

void RestRoom::OnEnter(Player* player) {
  int hpRestored = (player->GetMaxHP() * 20) / 100;
  int mpRestored = (player->GetMaxMP() * 20) / 100;

  player->RestoreHP(hpRestored);
  player->RestoreMP(mpRestored);

  m_resultText = m_dataManager->GetString("restored") +
                 std::to_string(hpRestored) +
                 m_dataManager->GetString("hp_and") +
                 std::to_string(mpRestored) + m_dataManager->GetString("mp.");
}
