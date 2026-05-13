#include "BossRoom.h"

#include "BattleManager.h"

BossRoom::BossRoom() : Room(RoomType::BOSS) {}

void BossRoom::OnEnter(Player* player) {
  BattleManager bm(player);
  bm.StartBattle(RoomType::BOSS);
  m_resultText = "Победа!";
}
