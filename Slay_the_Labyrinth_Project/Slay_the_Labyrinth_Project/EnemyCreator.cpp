#include "EnemyCreator.h"

#include <cstdlib>
#include <ctime>

EnemyCreator::EnemyCreator(DataManager* dm) : m_dataManager(dm) {}

Enemy* EnemyCreator::OnEnterB(RoomType type) {
  std::srand(std::time(nullptr));
  std::vector<Enemy> enemies;
  int randIndex;

  if (type == RoomType::MONSTER) {
    enemies = RegularEnemy(*m_dataManager);
  } else if (type == RoomType::ELITE) {
    enemies = EliteEnemy(*m_dataManager);
  } else {
    enemies = Bosses(*m_dataManager);
  }

  randIndex = std::rand() % enemies.size();
  return new Enemy(enemies[randIndex]);  // Возврат указателя на нового врага
}
