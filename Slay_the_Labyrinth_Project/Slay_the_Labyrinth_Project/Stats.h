#pragma once

#pragma once

struct Stats {
  const int WARRIOR_START_HP = 100;
  const int WARRIOR_START_ATK = 20;
  const int WARRIOR_START_SPD = 15;
  const int WARRIOR_START_INT = 10;
  const int WARRIOR_START_MP = 50;

  const int ROGUE_START_HP = 80;
  const int ROGUE_START_ATK = 15;
  const int ROGUE_START_SPD = 20;
  const int ROGUE_START_INT = 15;
  const int ROGUE_START_MP = 75;

  const int MAGE_START_HP = 70;
  const int MAGE_START_ATK = 10;
  const int MAGE_START_SPD = 13;
  const int MAGE_START_INT = 20;
  const int MAGE_START_MP = 100;

  int MaxHealth = 100;
  int CurrentHealth = 100;
  int MaxMana = 50;
  int CurrentMana = 50;

  int BonusAttack = 0;
  int BonusSpeed = 0;
  int BonusIntellect = 0;
  int BonusMaxHealth = 0;
  int BonusMaxMana = 0;

  int GetTotalAttack() const { return /*Аттака*/ +BonusAttack; }
  int GetTotalSpeed() const { return /*Скорость*/ +BonusSpeed; }
  int GetTotalIntellect() const { return /*Интеллект*/ +BonusIntellect; }
};
