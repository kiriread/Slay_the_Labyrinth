#pragma once

#pragma once

struct Stats {
  int MaxHP = 100;
  int CurrentHP = 100;
  int MaxMP = 50;
  int CurrentMP = 50;

  int BonusATK = 0;
  int BonusSPD = 0;
  int BonusINT = 0;
  int BonusMaxHP = 0;
  int BonusMaxMP = 0;

  //int GetTotalAttack() const { return /*Аттака*/ +BonusAttack; }
  //int GetTotalSpeed() const { return /*Скорость*/ +BonusSpeed; }
  //int GetTotalIntellect() const { return /*Интеллект*/ +BonusIntellect; }
};
