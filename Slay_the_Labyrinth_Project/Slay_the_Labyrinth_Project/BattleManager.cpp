#include "BattleManager.h"
#include "EnemyCreator.h"
#include "Enemy.h"
#include "Player.h"
#include "Spell.h"

BattleManager::BattleManager(Player* player, Game* game, DataManager* dm, ConsoleUtils* co)
    : m_player(player)
    , m_enemy(nullptr)
    , m_game(game)
    , m_sp("", 0, 0, 0)
    , m_pInitiative(0)
    , m_eInitiative(0)
    , m_isPlayerTurn(true)
    , m_dataManager(dm)
    , m_console(co)
    , m_totalATK(m_player->GetATK())
    , m_totalSPD(m_player->GetSPD())
    , m_totalEnemyATK(0)
    , m_totalEnemySPD(0)
    , m_rage_dur(0)
    , m_regen_dur(0)
    , m_spdPotion_dur(0)
    , m_dusk_dur(0)
    , m_frost_dur(0)
    , m_bossSkillCD(0)
    , m_fightType()
{
}

BattleManager::~BattleManager() {
    delete m_enemy;
}

void BattleManager::StartBattle(RoomType room) {
    EnemyCreator enemyCreator;
    m_enemy = enemyCreator.OnEnterB(room);
    m_fightType = room;
    if (room != RoomType::MONSTER && m_player->HasArtifact("trial_amulet")) {
        m_totalATK += 10;
    }
    m_spells = m_sp.GetSpells(m_player->GetClassName());
    m_totalEnemyATK = m_enemy->GetATK();
    m_totalEnemySPD = m_enemy->GetSPD();

    m_pInitiative = 0;
    m_eInitiative = 0;

    while (true) {
        m_console->ClearScreen();
        CalculateInitiative();

        if (m_isPlayerTurn) {
            PlayerTurn();
        }
        else {
            EnemyTurn();
        }

        if (m_enemy->GetCurrentHP() <= 0) {
            if (room == RoomType::MONSTER) {
                if (m_player->GetCurrentHP() == m_player->GetMaxHP()) {
                    m_player->AddPerfectionStats();
                }
                m_player->AddGold(300);
            }
            else if (room == RoomType::ELITE) {
                if (m_player->GetCurrentHP() == m_player->GetMaxHP()) {
                    m_player->AddPerfectionStats();
                }
                m_player->AddGold(600);
            }
            else {
                m_console->ClearScreen();
                m_console->Print(40, 2, m_dataManager->GetString("win"));
                int key = m_console->GetKey();
                std::exit(0);
            }


            break;
        }
        if (m_player->GetCurrentHP() <= 0) {
            if (m_player->HasArtifact("revival_amulet")) {
                m_player->RestoreHP(m_player->GetMaxHP() * 0.3);
                m_player->DelAmulet();
            }
            else {
                m_console->ClearScreen();
                m_console->Print(40, 2, m_dataManager->GetString("lose"));
                int key = m_console->GetKey();
                std::exit(0);
            }
        }
    }
}

void BattleManager::CalculateInitiative() {
    int playerSpd = m_totalSPD;
    int enemySpd = m_totalEnemySPD;

    if ((100 - m_pInitiative) / playerSpd <= (100 - m_eInitiative) / enemySpd) {
        m_isPlayerTurn = true;
        m_eInitiative += enemySpd * ((100 - m_pInitiative) / playerSpd);
        m_pInitiative = 0;
    }
    else {
        m_isPlayerTurn = false;
        m_pInitiative += playerSpd * ((100 - m_eInitiative) / enemySpd);
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
    if (m_player->HasArtifact("healing_sprout")) {
        m_player->RestoreHP(5);
    }
    m_console->ClearScreen();
    m_game->HUD(0);
    m_console->Print(40, 2, m_dataManager->GetString("your_turn"));
    EnemyHUD();
    int choice = 0;
    while (true) {
        if (choice == 0) {
            m_console->Print(40, 6, m_dataManager->GetString("sel_attack"));
            m_console->Print(40, 7, m_dataManager->GetString("spell"));
        }
        else {
            m_console->Print(40, 6, m_dataManager->GetString("attack"));
            m_console->Print(40, 7, m_dataManager->GetString("sel_spell"));
        }
        int key = m_console->GetKey();
        if (key == 224) {
            key = m_console->GetKey();
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
        m_console->ClearScreen();
        m_game->HUD(0);
        m_console->Print(40, 2, m_dataManager->GetString("your_turn"));
        EnemyHUD();
        SpellChoice();
    }
    m_console->ClearScreen();
    m_game->HUD(0);
    EnemyHUD();
    m_console->Print(40, 2, m_dataManager->GetString("you_attacked"));
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
    if (m_enemy->GetName() == "Чёрный дракон") {
        if (m_bossSkillCD == 0) {
            m_totalEnemyATK /= 2;
            m_totalEnemySPD /= 2;
            m_console->ClearScreen();
            m_game->HUD(0);
            EnemyHUD();
            m_console->Print(40, 2, m_dataManager->GetString("enemy_turn"));
            int key = m_console->GetKey();
            DragonCry();
            m_console->ClearScreen();
            m_game->HUD(0);
            EnemyHUD();
            m_console->Print(40, 2, m_dataManager->GetString("dragon_cry"));
            key = m_console->GetKey();
        }
        else {
            m_bossSkillCD -= 1;
            m_console->ClearScreen();
            m_game->HUD(0);
            EnemyHUD();
            m_console->Print(80, 6, m_dataManager->GetString("spell_cd") + std::to_string(m_bossSkillCD));
            m_console->Print(40, 2, m_dataManager->GetString("enemy_turn"));
            int key = m_console->GetKey();

            int damage = m_totalEnemyATK;
            m_player->RestoreHP(-damage);

            m_console->ClearScreen();
            m_game->HUD(0);
            EnemyHUD();
            m_console->Print(80, 6, m_dataManager->GetString("spell_cd") + std::to_string(m_bossSkillCD));
            m_console->Print(40, 2, m_dataManager->GetString("enemy_attacked"));
            key = m_console->GetKey();
        }
    }
    else if (m_enemy->GetName() == "Суккуб") {
        if (m_bossSkillCD == 0) {
            m_console->ClearScreen();
            m_game->HUD(0);
            EnemyHUD();
            m_console->Print(80, 6, m_dataManager->GetString("spell_cd") + std::to_string(m_bossSkillCD));
            m_console->Print(40, 2, m_dataManager->GetString("enemy_turn"));
            int key = m_console->GetKey();
            LifeSteal();
            m_console->ClearScreen();
            m_game->HUD(0);
            EnemyHUD();
            m_console->Print(40, 2, m_dataManager->GetString("succub_drain"));
            key = m_console->GetKey();
        }
        else {
            m_bossSkillCD -= 1;
            m_console->ClearScreen();
            m_game->HUD(0);
            EnemyHUD();
            m_console->Print(40, 2, m_dataManager->GetString("enemy_turn"));
            int key = m_console->GetKey();

            int damage = m_totalEnemyATK;
            m_player->RestoreHP(-damage);

            m_console->ClearScreen();
            m_game->HUD(0);
            EnemyHUD();
            m_console->Print(80, 6, m_dataManager->GetString("spell_cd") + std::to_string(m_bossSkillCD));
            m_console->Print(40, 2, m_dataManager->GetString("enemy_attacked"));
            key = m_console->GetKey();
        }
    }
    else {
        m_console->ClearScreen();
        m_game->HUD(0);
        EnemyHUD();
        m_console->Print(40, 2, m_dataManager->GetString("enemy_turn"));
        int key = m_console->GetKey();

        int damage = m_totalEnemyATK;
        m_player->RestoreHP(-damage);
        m_console->ClearScreen();
        m_game->HUD(0);
        EnemyHUD();
        m_console->Print(40, 2, m_dataManager->GetString("enemy_attacked"));
        key = m_console->GetKey();
    }
}
void BattleManager::EnemyHUD() {
    int x = 80;
    m_console->Print(x, 1, m_dataManager->GetString("en") + m_enemy->GetName());
    m_console->Print(x, 2, m_dataManager->GetString("en_hp") + std::to_string(m_enemy->GetCurrentHP()));
    m_console->Print(x, 3, m_dataManager->GetString("en_atk") + std::to_string(m_totalEnemyATK));
    m_console->Print(x, 4, m_dataManager->GetString("en_spd") + std::to_string(m_totalEnemySPD));
    m_console->Print(40, 4, m_dataManager->GetString("en_in") + std::to_string(m_eInitiative));
    m_console->Print(40, 3, m_dataManager->GetString("p_in") + std::to_string(m_pInitiative));
}

void BattleManager::SpellChoice() {
    int choice_spell = 0;
    std::string name1 = m_spells[0].GetName();
    std::string name2 = m_spells[1].GetName();
    std::string name3 = m_spells[2].GetName();
    while (true) {
        if (choice_spell == 0) {
            m_console->Print(40, 6, m_dataManager->GetString("sel_ch") + name1);
            m_console->Print(40, 7, m_dataManager->GetString("sel") + name2);
            m_console->Print(40, 8, m_dataManager->GetString("sel") + name3);
            m_console->Print(40, 9, m_dataManager->GetString("sel_return"));
        }
        else if (choice_spell == 1) {
            m_console->Print(40, 6, m_dataManager->GetString("sel") + name1);
            m_console->Print(40, 7, m_dataManager->GetString("sel_ch") + name2);
            m_console->Print(40, 8, m_dataManager->GetString("sel") + name3);
            m_console->Print(40, 9, m_dataManager->GetString("sel_return"));
        }
        else if (choice_spell == 2){
            m_console->Print(40, 6, m_dataManager->GetString("sel") + name1);
            m_console->Print(40, 7, m_dataManager->GetString("sel") + name2);
            m_console->Print(40, 8, m_dataManager->GetString("sel_ch") + name3);
            m_console->Print(40, 9, m_dataManager->GetString("sel_return"));
        }
        else {
            m_console->Print(40, 6, m_dataManager->GetString("sel") + name1);
            m_console->Print(40, 7, m_dataManager->GetString("sel") + name2);
            m_console->Print(40, 8, m_dataManager->GetString("sel") + name3);
            m_console->Print(40, 9, m_dataManager->GetString("sel_ch_return"));
        }
        int key = m_console->GetKey();
        if (key == 224) {
            key = m_console->GetKey();
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
            if (name1.size() == 7) {
                m_rage_dur = m_spells[0].GetMaxDur();
                m_totalATK = m_sp.Rage(m_player);
            }
            else if (name1.size() == 13) {
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
            if (name2.size() == 17) {
                m_enemy->TakeDamage(m_sp.Sweeping_strike());
            }
            else if (name2.size() == 15) {
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
            if (name3.size() == 18) {
                m_regen_dur = m_spells[2].GetMaxDur();
            }
            else if (name3.size() == 13) {
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

void BattleManager::DragonCry() {
    m_totalEnemySPD *= 2;
    m_totalEnemyATK *= 2;
    m_bossSkillCD = 3;
}

void BattleManager::LifeSteal() {
    m_player->RestoreHP(-40);
    m_enemy->TakeDamage(-40);
    m_bossSkillCD = 3;
}