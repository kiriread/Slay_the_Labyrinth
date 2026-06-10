#pragma once

#include "Room.h"
#include "Enemy.h"
#include "DataManager.h"

enum class enemyVariants {NAME = 1, HP = 2, ATK = 3, SPD = 4};

class EnemyCreator {
public:
    EnemyCreator(DataManager* dm);  
    Enemy* OnEnterB(RoomType type);
private:
    DataManager* m_dataManager;     
};
