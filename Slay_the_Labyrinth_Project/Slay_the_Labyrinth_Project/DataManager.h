#pragma once

#include <string>
#include <vector>

#include "Room.h"
#include "Stats.h"
#include "json.hpp"

class DataManager {
 private:
  nlohmann::json m_classData;
  nlohmann::json m_roomData;
  nlohmann::json m_stringsData;
  nlohmann::json m_artifactsData;
  nlohmann::json m_spellsData;
  std::string UTF8to1251(const std::string& utf8) const;

 public:
  // Классы
  void LoadClasses(const std::string& filepath);
  Stats GetClassStats(const std::string& classId);
  std::string GetClassNamee(const std::string& classId);
  std::vector<std::string> GetClassSpells(const std::string& classId);

  // Комнаты
  void LoadRooms(const std::string& filepath);
  std::string GetRoomName(RoomType type);
  std::string GetRoomDescription(RoomType type);
  std::string RoomTypeToString(RoomType type);

  // Строки
  void LoadStrings(const std::string& filepath);
  std::string GetString(const std::string& key);

  // Артефакты
  void LoadArtifacts(const std::string& filepath);
  std::string GetArtifactName(const std::string& id) const;
  std::string GetArtifactDescription(const std::string& id) const;
  int GetArtifactPrice(const std::string& id) const;
  std::vector<std::string> GetRandomArtifactIds(int count) const;

  // Заклинания
  void LoadSpells(const std::string& filepath);
  std::string GetSpellName(const std::string& id) const;
  int GetSpellMana(const std::string& id) const;
};
