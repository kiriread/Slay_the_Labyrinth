#pragma once

struct Stats {
    int MaxHP = 100;
    int CurrentHP = 100;
    int MaxMP = 50;
    int CurrentMP = 50;

    // Stubs
    int ATK = 10;
    int SPD = 10;
    int INT = 10;

    int BonusATK = 0;
    int BonusSPD = 0;
    int BonusINT = 0;
    int BonusMaxHP = 0;
    int BonusMaxMP = 0;

    // Getters
    int GetTotalATK() const { return ATK + BonusATK; }
    int GetTotalSPD() const { return SPD + BonusSPD; }
    int GetTotalINT() const { return INT + BonusINT; }
    int GetTotalMaxHP() const { return MaxHP + BonusMaxHP; }
    int GetTotalMaxMP() const { return MaxMP + BonusMaxMP; }
};