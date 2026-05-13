#pragma once

#include <string>
#include <vector>

#include "Stats.h"

class Player {
 private:
  std::string m_className;
  Stats m_stats;
  int m_gold = 1000;
  std::vector<std::string> m_inventory;

 public:
  Player(std::string className, Stats stats);

  // more Getters
  std::string GetClassName() const { return m_className; }
  int GetCurrentHP() const { return m_stats.CurrentHP; }
  int GetMaxHP() const { return m_stats.GetTotalMaxHP(); }
  int GetCurrentMP() const { return m_stats.CurrentMP; }
  int GetMaxMP() const { return m_stats.GetTotalMaxMP(); }
  int GetATK() const { return m_stats.GetTotalATK(); }
  int GetSPD() const { return m_stats.GetTotalSPD(); }
  int GetINT() const { return m_stats.GetTotalINT(); }

  void RestoreHP(int amount);
  void RestoreMP(int aomount);

  int GetGold() const;
  void AddGold(int amount);
  bool SpendGold(int amount);
  void AddArtifact(const std::string& id);
  const std::vector<std::string>& GetInventory() const;
};
