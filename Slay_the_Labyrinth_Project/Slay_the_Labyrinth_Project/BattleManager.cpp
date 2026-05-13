#include "BattleManager.h"
#include "EnemyCreator.h"
#include "Enemy.h"
#include "Player.h"

BattleManager::BattleManager(Player* player, Game* game)
    : m_player(player)
    , m_enemy(nullptr)
    , m_game(game)
    , m_pInitiative(0)
    , m_eInitiative(0)
    , m_isPlayerTurn(true)
    , m_dataManager()
    , m_console()
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
        m_console.ClearScreen();
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

    if ((100 - m_pInitiative) / playerSpd <= (100 - m_eInitiative) / enemySpd) {
        m_isPlayerTurn = true;
        m_eInitiative = enemySpd * ((100 - m_pInitiative) / playerSpd);
        m_pInitiative = 0;
    }
    else {
        m_isPlayerTurn = false;
        m_pInitiative = playerSpd * ((100 - m_eInitiative) / enemySpd);
        m_eInitiative = 0;
    }
}

void BattleManager::PlayerTurn() {
    m_console.ClearScreen();
    m_game->HUD(0);
    m_console.Print(0, 0, "Ваш ход:");
    EnemyHUD();
    int key = m_console.GetKey();

    int damage = m_player->GetATK();
    m_enemy->TakeDamage(damage);

    m_console.ClearScreen();
    m_game->HUD(0);
    EnemyHUD();
    m_console.Print(0, 0, "Вы атаковали:");
    key = m_console.GetKey();
}

void BattleManager::EnemyTurn() {
    m_console.ClearScreen();
    m_game->HUD(0);
    EnemyHUD();
    m_console.Print(0, 0, "Ход врага:");
    int key = m_console.GetKey();

    int damage = m_enemy->GetATK();
    m_player->RestoreHP(-damage);
    
    m_console.ClearScreen();
    m_game->HUD(0);
    EnemyHUD();
    m_console.Print(0, 0, "Враг атаковал:");
    key = m_console.GetKey();
}
void BattleManager::EnemyHUD() {
    int x = 80;
    m_console.Print(x, 1, "Враг: " + m_enemy->GetName());
    m_console.Print(x, 2, "HP: " + std::to_string(m_enemy->GetCurrentHP()));
    m_console.Print(x, 3, "ATK: " + std::to_string(m_enemy->GetATK()));
    m_console.Print(x, 4, "SPD: " + std::to_string(m_enemy->GetSPD()));
    m_console.Print(x, 5, "Инициативность врага: " + std::to_string(m_eInitiative));
    if (m_isPlayerTurn)
        m_console.Print(0, 0, "Ваш ход:");
}