#include "DataManager.h"

#include <windows.h>

#include <fstream>
#include <iostream>

void DataManager::LoadClasses(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Ошибка: не удалось открыть " << filepath << std::endl;
    return;
  }
  file >> m_classData;
  file.close();
}

Stats DataManager::GetClassStats(const std::string& classId) {
  Stats stats;

  if (!m_classData.contains(classId)) {
    std::cerr << "Ошибка: класс '" << classId << "' не найден в JSON"
              << std::endl;
    return stats;
  }

  auto& baseStats = m_classData[classId]["base_stats"];

  stats.MaxHP = baseStats["max_hp"];
  stats.ATK = baseStats["atk"];
  stats.SPD = baseStats["spd"];
  stats.INT = baseStats["int"];
  stats.MaxMP = baseStats["max_mp"];

  stats.CurrentHP = stats.MaxHP;
  stats.CurrentMP = stats.MaxMP;

  return stats;
}

std::string DataManager::UTF8to1251(const std::string& utf8) {
  int size = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
  std::wstring wtext(size, L'\0');
  MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &wtext[0], size);

  int size1251 =
      WideCharToMultiByte(1251, 0, &wtext[0], -1, nullptr, 0, nullptr, nullptr);
  std::string result(size1251, '\0');
  WideCharToMultiByte(1251, 0, &wtext[0], -1, &result[0], size1251, nullptr,
                      nullptr);

  return result;
}

std::string DataManager::GetClassNamee(const std::string& classId) {
  if (!m_classData.contains(classId)) {
    return "Неизвестно";
  }
  return UTF8to1251(m_classData[classId]["name"]);
}

std::vector<std::string> DataManager::GetClassSpells(
    const std::string& classId) {
  std::vector<std::string> spells;

  if (!m_classData.contains(classId)) {
    return spells;
  }

  for (auto& spell : m_classData[classId]["spells"]) {
    spells.push_back(spell);
  }

  return spells;
}
