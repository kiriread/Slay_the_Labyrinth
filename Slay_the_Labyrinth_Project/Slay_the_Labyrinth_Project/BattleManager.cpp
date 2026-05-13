#include "BattleManager.h"
#include "EnemyCreator.h"
#include "Enemy.h"
#include "Player.h"

BattleManager::BattleManager(Player* player)
    : m_player(player)
    , m_enemy(nullptr)
    , m_pInitiative(0)
    , m_eInitiative(0)
    , m_isPlayerTurn(true)
{
}

BattleManager::~BattleManager() {
    delete m_enemy;
}

void BattleManager::StartBattle(RoomType room) {
    EnemyCreator enemyCreator;
    m_enemy = enemyCreator.OnEnterB(room);

    m_pInitiative = 0;
    m_eInitiative = 0;

    while (true) {
        CalculateInitiative();

        if (m_isPlayerTurn) {
            PlayerTurn();
        }
        else {
            EnemyTurn();
        }

        if (m_enemy->GetCurrentHP() <= 0) {
            break;
        }
        if (m_player->GetCurrentHP() <= 0) {
            break;
        }
    }
}

void BattleManager::CalculateInitiative() {
    int playerSpd = m_player->GetSPD();
    int enemySpd = m_enemy->GetSPD();

    if (m_pInitiative >= 10) {
        m_isPlayerTurn = true;
        m_pInitiative = 0;
    }
    else if (m_eInitiative >= 10) {
        m_isPlayerTurn = false;
        m_eInitiative = 0;
    }
    else {
        m_pInitiative += playerSpd;
        m_eInitiative += enemySpd;
    }
}

void BattleManager::PlayerTurn() {
    int damage = m_player->GetATK();
    m_enemy->TakeDamage(damage);
}

void BattleManager::EnemyTurn() {
    int damage = m_enemy->GetATK();
    m_player->RestoreHP(-damage);
}