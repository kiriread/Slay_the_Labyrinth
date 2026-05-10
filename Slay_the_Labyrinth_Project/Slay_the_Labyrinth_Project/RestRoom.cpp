#include "RestRoom.h"

#include "Player.h"

RestRoom::RestRoom() : Room(RoomType::REST) {
  m_description =
      "Вы находите тихий уголок. Воздух теплый и успокаивающий. Вас манит "
      "остановиться и восстановить HP и MP";
}

void RestRoom::OnEnter(Player* player) {
  int hpRestored = (player->GetMaxHP() * 20) / 100;
  int mpRestored = (player->GetMaxMP() * 20) / 100;

  player->RestoreHP(hpRestored);
  player->RestoreMP(mpRestored);

  m_description += "\nВосстановлено " + std::to_string(hpRestored) + " HP и " +
                   std::to_string(mpRestored) + " MP.";
}
