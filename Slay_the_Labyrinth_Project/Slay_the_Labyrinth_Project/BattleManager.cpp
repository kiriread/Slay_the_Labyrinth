#include "BattleManager.h"

#include "Enemy.h"
#include "EnemyCreator.h"
#include "Player.h"
#include "Spell.h"

BattleManager::BattleManager(Player* player, Game* game, DataManager* dm,
                             ConsoleUtils* co)
    : m_player(player),
      m_enemy(nullptr),
      m_game(game),
      m_sp("", 0, 0, 0),
      m_pInitiative(0),
      m_eInitiative(0),
      m_isPlayerTurn(true),
      m_dataManager(dm),
      m_console(co),
      m_totalEnemyATK(0),
      m_totalEnemySPD(0),
      m_rage_dur(0),
      m_regen_dur(0),
      m_spdPotion_dur(0),
      m_dusk_dur(0),
      m_frost_dur(0),
      m_bossSkillCD(0),
      m_fightType() {}

BattleManager::~BattleManager() { delete m_enemy; }

void BattleManager::StartBattle(RoomType room) {
  m_player->SaveStats();
  EnemyCreator enemyCreator(m_dataManager);
  m_enemy = enemyCreator.OnEnterB(room);
  m_fightType = room;
  if (room != RoomType::MONSTER && m_player->HasArtifact("trial_amulet")) {
    m_player->ChangeBonusATKSP(0, 0, 1, 0);
  }
  m_spells = m_sp.GetSpells(m_player->GetClassName(), *m_dataManager);

  m_totalEnemyATK = m_enemy->GetATK();
  m_totalEnemySPD = m_enemy->GetSPD();

  m_pInitiative = 0;
  m_eInitiative = 0;

  while (true) {
    m_console->ClearScreen();
    CalculateInitiative();

    if (m_isPlayerTurn) {
      PlayerTurn();
    } else {
      EnemyTurn();
    }

    if (m_enemy->GetCurrentHP() <= 0) {
      if (room == RoomType::MONSTER) {
        if (m_rage_dur != 0) m_player->ChangeBonusATKSP(0, 0, 0, 0);
        if (m_spdPotion_dur != 0) m_player->ChangeBonusSPDSP(0, 0);
        if (m_player->GetCurrentHP() == m_player->GetMaxHP()) {
          m_player->AddPerfectionStats();
        }
        m_player->AddGold(300);
      } else if (room == RoomType::ELITE) {
        if (m_rage_dur != 0) m_player->ChangeBonusATKSP(0, 0, 0, 0);
        if (m_spdPotion_dur != 0) m_player->ChangeBonusSPDSP(0, 0);
        if (m_player->HasArtifact("trial_amulet"))
          m_player->ChangeBonusATKSP(0, 0, 0, 1);
        if (m_player->GetCurrentHP() == m_player->GetMaxHP()) {
          m_player->AddPerfectionStats();
        }
        m_player->AddGold(600);
      } else {
        m_console->ClearScreen();
        m_console->Print(40, 2, m_dataManager->GetString("win"));
        int key = m_console->GetKey();
        std::exit(0);
      }
      m_player->RestoreStats();
      break;
    }
    if (m_player->GetCurrentHP() <= 0) {
      if (m_player->HasArtifact("revival_amulet")) {
        m_player->RestoreHP(m_player->GetMaxHP() * 0.3);
        m_player->DelAmulet();
      } else {
        m_console->ClearScreen();
        m_console->Print(40, 2, m_dataManager->GetString("lose"));
        int key = m_console->GetKey();
        std::exit(0);
      }
    }
  }
}

void BattleManager::CalculateInitiative() {
  int playerSpd = m_player->GetSPD();
  int enemySpd = m_totalEnemySPD;

  if ((100 - m_pInitiative) / playerSpd <= (100 - m_eInitiative) / enemySpd) {
    m_isPlayerTurn = true;
    m_eInitiative += enemySpd * ((100 - m_pInitiative) / playerSpd);
    m_pInitiative = 0;
  } else {
    m_isPlayerTurn = false;
    m_pInitiative += playerSpd * ((100 - m_eInitiative) / enemySpd);
    m_eInitiative = 0;
  }
}

void BattleManager::PlayerTurn() {
  if (m_rage_dur != 0) {
    m_rage_dur -= 1;
    if (m_rage_dur == 0) {
      m_player->ChangeBonusATKSP(0, 0, 0, 0);
    }
  }
  if (m_regen_dur != 0) {
    m_regen_dur -= 1;
    m_player->RestoreHP(m_sp.Regeneration_potion());
  }
  if (m_spdPotion_dur != 0) {
    m_spdPotion_dur -= 1;
    if (m_spdPotion_dur == 0) {
      m_player->ChangeBonusSPDSP(0, 0);
    }
  }
  if (m_player->HasArtifact("healing_sprout")) {
    m_player->RestoreHP(5);
  }
  if (m_player->HasArtifact("diadem")) {
    m_player->RestoreMP(5);
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
    } else {
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
  int damage = m_player->GetATK();
  if (choice == 0)
    m_enemy->TakeDamage(damage);
  else {
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
  if (m_frost_dur > 0) {
    m_frost_dur--;
    if (m_frost_dur == 0) {
      m_enemy->RestoreSPD();
      m_totalEnemySPD = m_enemy->GetSPD();
    }
  }

  if (m_enemy->GetName().size() == 14 && m_fightType == RoomType::BOSS) {
    if (m_bossSkillCD == 0) {
      if (!m_isFCry) {
        m_totalEnemyATK /= 1.5;
        m_totalEnemySPD /= 1.5;
      }
      m_isFCry = false;
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
    } else {
      m_bossSkillCD -= 1;
      m_console->ClearScreen();
      m_game->HUD(0);
      EnemyHUD();
      m_console->Print(
          80, 6,
          m_dataManager->GetString("spell_cd") + std::to_string(m_bossSkillCD));
      m_console->Print(40, 2, m_dataManager->GetString("enemy_turn"));
      int key = m_console->GetKey();

      int damage = m_totalEnemyATK;
      m_player->RestoreHP(-damage);

      m_console->ClearScreen();
      m_game->HUD(0);
      EnemyHUD();
      m_console->Print(
          80, 6,
          m_dataManager->GetString("spell_cd") + std::to_string(m_bossSkillCD));
      m_console->Print(40, 2, m_dataManager->GetString("enemy_attacked"));
      key = m_console->GetKey();
    }
  } else if (m_fightType == RoomType::BOSS) {
    if (m_bossSkillCD == 0) {
      m_console->ClearScreen();
      m_game->HUD(0);
      EnemyHUD();
      m_console->Print(
          80, 6,
          m_dataManager->GetString("spell_cd") + std::to_string(m_bossSkillCD));
      m_console->Print(40, 2, m_dataManager->GetString("enemy_turn"));
      int key = m_console->GetKey();
      LifeSteal();
      m_console->ClearScreen();
      m_game->HUD(0);
      EnemyHUD();
      m_console->Print(40, 2, m_dataManager->GetString("succub_drain"));
      key = m_console->GetKey();
    } else {
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
      m_console->Print(
          80, 6,
          m_dataManager->GetString("spell_cd") + std::to_string(m_bossSkillCD));
      m_console->Print(40, 2, m_dataManager->GetString("enemy_attacked"));
      key = m_console->GetKey();
    }
  } else {
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
  m_console->Print(x, 2,
                   m_dataManager->GetString("en_hp") +
                       std::to_string(m_enemy->GetCurrentHP()));
  m_console->Print(
      x, 3,
      m_dataManager->GetString("en_atk") + std::to_string(m_totalEnemyATK));
  m_console->Print(
      x, 4,
      m_dataManager->GetString("en_spd") + std::to_string(m_totalEnemySPD));
  m_console->Print(
      40, 4, m_dataManager->GetString("en_in") + std::to_string(m_eInitiative));
  m_console->Print(
      40, 3, m_dataManager->GetString("p_in") + std::to_string(m_pInitiative));
}

void BattleManager::SpellChoice() {
  m_console->ClearScreen();
  m_game->HUD(0);
  m_console->Print(40, 2, m_dataManager->GetString("your_turn"));
  EnemyHUD();
  int choice_spell = 0;
  std::string name1 = m_spells[0].GetName();
  std::string name2 = m_spells[1].GetName();
  std::string name3 = m_spells[2].GetName();
  while (true) {
    if (choice_spell == 0) {
      m_console->Print(40, 6, m_dataManager->GetString("sel_ch") + name1);
      m_console->Print(40, 7, m_dataManager->GetString("sel") + name2);
      m_console->Print(40, 8, m_dataManager->GetString("sel") + name3);
      m_console->Print(40, 10, m_dataManager->GetString("sel_return"));
    } else if (choice_spell == 1) {
      m_console->Print(40, 6, m_dataManager->GetString("sel") + name1);
      m_console->Print(40, 7, m_dataManager->GetString("sel_ch") + name2);
      m_console->Print(40, 8, m_dataManager->GetString("sel") + name3);
      m_console->Print(40, 10, m_dataManager->GetString("sel_return"));
    } else if (choice_spell == 2) {
      m_console->Print(40, 6, m_dataManager->GetString("sel") + name1);
      m_console->Print(40, 7, m_dataManager->GetString("sel") + name2);
      m_console->Print(40, 8, m_dataManager->GetString("sel_ch") + name3);
      m_console->Print(40, 10, m_dataManager->GetString("sel_return"));
    } else {
      m_console->Print(40, 6, m_dataManager->GetString("sel") + name1);
      m_console->Print(40, 7, m_dataManager->GetString("sel") + name2);
      m_console->Print(40, 8, m_dataManager->GetString("sel") + name3);
      m_console->Print(40, 10, m_dataManager->GetString("sel_ch_return"));
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
        m_player->ChangeBonusATKSP(m_sp.Rage(m_player), 1, 0, 0);
      } else if (name1.size() == 13) {
        m_enemy->TakeDamage(m_sp.Backstab(m_player->GetINT()));
      } else {
        m_enemy->TakeDamage(m_sp.Fireball(m_player->GetINT()));
      }
    } else {
      m_console->Print(42, 12, m_dataManager->GetString("l_mana"));
      int key = m_console->GetKey();
      SpellChoice();
    }
  } else if (choice_spell == 1) {
    if (m_player->GetCurrentMP() >= m_spells[1].GetCost()) {
      m_player->RestoreMP(-m_spells[1].GetCost());
      if (name2.size() == 17) {
        m_enemy->TakeDamage(m_sp.Sweeping_strike(m_player->GetINT()));
      } else if (name2.size() == 15) {
        m_spdPotion_dur = m_spells[1].GetMaxDur();
        m_player->ChangeBonusSPDSP(m_sp.Speed_potion(m_player), 1);
      } else {
        m_frost_dur = m_spells[1].GetMaxDur();
        int newSPD = m_sp.Frost_vortex(m_enemy);
        m_enemy->SetSPD(newSPD);
        m_totalEnemySPD = newSPD;
      }
    } else {
      m_console->Print(42, 12, m_dataManager->GetString("l_mana"));
      int key = m_console->GetKey();
      SpellChoice();
    }
  } else if (choice_spell == 2) {
    if (m_player->GetCurrentMP() >= m_spells[2].GetCost()) {
      m_player->RestoreMP(-m_spells[2].GetCost());
      if (name3.size() == 18) {
        m_regen_dur = m_spells[2].GetMaxDur();
      } else if (name3.size() == 13) {
        m_dusk_dur = m_spells[2].GetMaxDur();
        m_totalEnemyATK = m_sp.Dust_in_eyes(m_enemy);
      } else {
        m_player->RestoreHP(m_sp.Healing(m_player->GetINT()));
      }
    } else {
      m_console->Print(42, 12, m_dataManager->GetString("l_mana"));
      int key = m_console->GetKey();
      SpellChoice();
    }
  } else {
    PlayerTurn();
  }
}

void BattleManager::DragonCry() {
  m_totalEnemySPD *= 1.5;
  m_totalEnemyATK *= 1.5;
  m_bossSkillCD = 3;
}

void BattleManager::LifeSteal() {
  m_player->RestoreHP(-10);
  m_enemy->TakeDamage(-10);
  m_bossSkillCD = 3;
}
