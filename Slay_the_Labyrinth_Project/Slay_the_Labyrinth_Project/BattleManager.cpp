#include "BattleManager.h"
#include "EnemyCreator.h"
#include "Enemy.h"
#include "Player.h"
#include "Spell.h"

BattleManager::BattleManager(Player* player, Game* game)
    : m_player(player)
    , m_enemy(nullptr)
    , m_game(game)
    , m_sp("", 0, 0, 0)
    , m_pInitiative(0)
    , m_eInitiative(0)
    , m_isPlayerTurn(true)
    , m_dataManager()
    , m_console()
    , m_totalATK(m_player->GetATK())
    , m_totalSPD(m_player->GetSPD())
    , m_rage_dur(0)
    , m_regen_dur(0)
    , m_spdPotion_dur(0)
    , m_dusk_dur(0)
    , m_frost_dur(0)
{
}

BattleManager::~BattleManager() {
    delete m_enemy;
}

void BattleManager::StartBattle(RoomType room) {
    EnemyCreator enemyCreator;
    m_enemy = enemyCreator.OnEnterB(room);
    m_spells = m_sp.GetSpells(m_player->GetClassName());

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
    int playerSpd = m_totalSPD;
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
    if (m_rage_dur != 0) {
        m_rage_dur -= 1;
        if (m_rage_dur == 0) {
            m_totalATK /= 2;
        }
    }
    if (m_regen_dur != 0) {
        m_regen_dur -= 1;
        if (m_regen_dur != 0) {
            m_player->RestoreHP(m_sp.Regeneration_potion());
        }
    }
    if (m_spdPotion_dur != 0) {
        m_spdPotion_dur -= 1;
        if (m_spdPotion_dur == 0) {
            m_totalSPD /= 2;
        }
    }
    m_console.ClearScreen();
    m_game->HUD(0);
    m_console.Print(0, 0, "Ваш ход:");
    EnemyHUD();
    int choice = 0;
    while (true) {
        if (choice == 0) {
            m_console.Print(2, 20, "> Атака");
            m_console.Print(2, 21, "  Заклинания");
        }
        else {
            m_console.Print(2, 20, "  Атака");
            m_console.Print(2, 21, "> Заклинания");
        }
        int key = m_console.GetKey();
        if (key == 224) {
            key = m_console.GetKey();
            if (key == 72) {
                choice--;
                if (choice < 0) choice = 1;
            }
            if (key == 80) {
                choice++;
                if (choice > 1) choice = 0;
            }
        }
        if (key == 13) break;
    }
    int damage = m_totalATK;
    if (choice == 0)
        m_enemy->TakeDamage(damage);
    else {
        m_console.ClearScreen();
        m_game->HUD(0);
        m_console.Print(0, 0, "Ваш ход:");
        EnemyHUD();
        SpellChoice();
    }
    m_console.ClearScreen();
    m_game->HUD(0);
    EnemyHUD();
    m_console.Print(0, 0, "Вы атаковали:");
    //key = m_console.GetKey();
}

void BattleManager::EnemyTurn() {
    if (m_dusk_dur != 0) {
        m_dusk_dur -= 1;
        if (m_dusk_dur == 0) {
            m_totalEnemyATK *= 2;
        }
    }
    if (m_frost_dur != 0) {
        m_frost_dur -= 1;
        if (m_frost_dur == 0) {
            m_totalEnemySPD *= 2;
        }
    }
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
}

void BattleManager::SpellChoice() {
    int choice_spell = 0;
    std::string name1 = m_spells[0].GetName();
    std::string name2 = m_spells[1].GetName();
    std::string name3 = m_spells[2].GetName();
    while (true) {
        if (choice_spell == 0) {
            m_console.Print(2, 21, "> " + name1);
            m_console.Print(2, 22, "  " + name2);
            m_console.Print(2, 23, "  " + name3);
            m_console.Print(2, 24, "  Вернуться на выбор атаки");
        }
        else if (choice_spell == 1) {
            m_console.Print(2, 21, "  " + name1);
            m_console.Print(2, 22, "> " + name2);
            m_console.Print(2, 23, "  " + name3);
            m_console.Print(2, 24, "  Вернуться на выбор атаки");
        }
        else if (choice_spell == 2){
            m_console.Print(2, 21, "  " + name1);
            m_console.Print(2, 22, "  " + name2);
            m_console.Print(2, 23, "> " + name3);
            m_console.Print(2, 24, "  Вернуться на выбор атаки");
        }
        else {
            m_console.Print(2, 21, "  " + name1);
            m_console.Print(2, 22, "  " + name2);
            m_console.Print(2, 23, "  " + name3);
            m_console.Print(2, 24, ">  Вернуться на выбор атаки");
        }
        int key = m_console.GetKey();
        if (key == 224) {
            key = m_console.GetKey();
            if (key == 72) {
                choice_spell--;
                if (choice_spell < 0) choice_spell = 3;
            }
            if (key == 80) {
                choice_spell++;
                if (choice_spell > 3) choice_spell = 0;
            }
        }
        if (key == 13) break;
    }
    if (choice_spell == 0) {
        if (m_player->GetCurrentMP() >= m_spells[0].GetCost()) {
            m_player->RestoreMP(-m_spells[0].GetCost());
            if (name1 == "Rage") {
                m_rage_dur = m_spells[0].GetMaxDur();
                m_totalATK = m_sp.Rage(m_player);
            }
            else if (name1 == "Backstab") {
                m_enemy->TakeDamage(m_sp.Backstab());
            }
            else {
                m_enemy->TakeDamage(m_sp.Fireball());
            }
        }
        else {
            SpellChoice();
        }
    }
    else if (choice_spell == 1) {
        if (m_player->GetCurrentMP() >= m_spells[1].GetCost()) {
            m_player->RestoreMP(-m_spells[1].GetCost());
            if (name2 == "Sweeping_strike") {
                m_enemy->TakeDamage(m_sp.Sweeping_strike());
            }
            else if (name2 == "Speed_potion") {
                m_spdPotion_dur = m_spells[1].GetMaxDur();
                m_totalSPD = m_sp.Speed_potion(m_player);
            }
            else {
                m_frost_dur = m_spells[1].GetMaxDur();
                m_totalEnemySPD = m_sp.Frost_vortex(m_enemy);
            }
        }
        else {
            SpellChoice();
        }
    }
    else if (choice_spell == 2){
        if (m_player->GetCurrentMP() >= m_spells[2].GetCost()) {
            m_player->RestoreMP(-m_spells[2].GetCost());
            if (name3 == "Regeneration_potion") {
                m_regen_dur = m_spells[2].GetMaxDur();
            }
            else if (name3 == "") {
                m_dusk_dur = m_spells[2].GetMaxDur();
                m_totalEnemyATK = m_sp.Dust_in_eyes(m_enemy);
            }
            else {
                m_player->RestoreHP(m_sp.Healing());
            }
        }
        else {
            SpellChoice();
        }
    }
    else {
        PlayerTurn();
    }
}