#include <ctime>
#include <string>
#include <variant>

#include "EnemyCreator.h"
#include "Enemy.h"

Enemy EnemyCreator::OnEnterB(RoomType type) {
	std::srand(std::time(nullptr));
	std::vector<Enemy> enemies;
	int randIndex;

	if (type == RoomType::MONSTER) {
		enemies = RegularEnemy();
	}
	else if (type == RoomType::ELITE) {
		enemies	= EliteEnemy();
	}
	else {
		enemies = Bosses();
	}
	randIndex = std::rand() % enemies.size();
	Enemy& selectedEnemy = enemies[randIndex];
	return selectedEnemy;
}