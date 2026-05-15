#include "RestRoom.h"

#include "Game.h"
#include "Player.h"
#include "Stats.h"

RestRoom::RestRoom(DataManager* dm, ConsoleUtils* console, Game* game)
    : Room(RoomType::REST),
      m_dataManager(dm),
      m_console(console),
      m_game(game) {}

void RestRoom::OnEnter(Player* player) {
  int bonusMaxHP = 0;
  int bonusMaxMP = 0;

  // Бонус к максимуму при ночлеге (снотворное, увлажнитель)
  if (player->HasArtifact("sleeping_pill")) {
    player->AddMaxHP(5);
    bonusMaxHP = 5;
  }
  if (player->HasArtifact("humidifier")) {
    player->AddMaxMP(15);
    bonusMaxMP = 15;
  }

  // Базовое восстановление 20%
  int hpRestored = (player->GetMaxHP() * 20) / 100;
  int mpRestored = (player->GetMaxMP() * 20) / 100;

  // Бонусы от артефактов (+ фиксированные значения)
  if (player->HasArtifact("sleep_pillow")) hpRestored += 10;
  if (player->HasArtifact("sleep_blanket")) mpRestored += 20;

  player->RestoreHP(hpRestored);
  player->RestoreMP(mpRestored);

  m_resultText = m_dataManager->GetString("restored") +
                 std::to_string(hpRestored) +
                 m_dataManager->GetString("hp_and") +
                 std::to_string(mpRestored) + m_dataManager->GetString("mp.");

  if (bonusMaxHP > 0) {
    m_resultText +=
        m_dataManager->GetString("max_hp") + std::to_string(bonusMaxHP) + ".";
  }
  if (bonusMaxMP > 0) {
    m_resultText +=
        m_dataManager->GetString("max_mp") + std::to_string(bonusMaxMP) + ".";
  }
}
