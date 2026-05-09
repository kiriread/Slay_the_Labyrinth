#pragma once

struct Stats {
  // Максимальные значения
  int MaxHP = 100;
  int MaxMP = 50;

  // Текущие значения
  int CurrentHP = 100;
  int CurrentMP = 50;

  // Базовые характеристики
  int ATK = 10;
  int SPD = 10;
  int INT = 10;

  // Бонусы от артефактов
  int BonusATK = 0;
  int BonusSPD = 0;
  int BonusINT = 0;
  int BonusMaxHP = 0;
  int BonusMaxMP = 0;

  // Итоговые значения с учётом бонусов
  int GetTotalAttack() const { return ATK + BonusATK; }
  int GetTotalSpeed() const { return SPD + BonusSPD; }
  int GetTotalIntellect() const { return INT + BonusINT; }
  int GetTotalMaxHP() const { return MaxHP + BonusMaxHP; }
  int GetTotalMaxMP() const { return MaxMP + BonusMaxMP; }
};
