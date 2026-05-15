#include "DataManager.h"

#include <windows.h>

#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>

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

std::string DataManager::UTF8to1251(const std::string& utf8) const {
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

void DataManager::LoadRooms(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть " << filepath << std::endl;
        return;
    }
    file >> m_roomData;
    file.close();
}

std::string DataManager::RoomTypeToString(RoomType type) {
    switch (type) {
    case RoomType::REST:    return "REST";
    case RoomType::SHOP:    return "SHOP";
    case RoomType::MONSTER: return "MONSTER";
    case RoomType::ELITE:   return "ELITE";
    case RoomType::BOSS:    return "BOSS";
    default:                return "";
    }
}

std::string DataManager::GetRoomName(RoomType type) {
    std::string key = RoomTypeToString(type);
    return UTF8to1251(m_roomData["room_names"][key]);
}

std::string DataManager::GetRoomDescription(RoomType type) {
    std::string key = RoomTypeToString(type);
    return UTF8to1251(m_roomData["room_descriptions"][key]);
}

void DataManager::LoadStrings(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть " << filepath << std::endl;
        return;
    }
    file >> m_stringsData;
    file.close();
}

std::string DataManager::GetString(const std::string& key) {
    if (!m_stringsData.contains(key)) return "";
    return UTF8to1251(m_stringsData[key]);
}

void DataManager::LoadArtifacts(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть " << filepath << std::endl;
        return;
    }
    file >> m_artifactsData;
    file.close();
}

std::string DataManager::GetArtifactName(const std::string& id) const {
    if (!m_artifactsData.contains(id)) {
        return "Неизвестно";
    }
    return UTF8to1251(m_artifactsData[id]["name"]);
}

std::string DataManager::GetArtifactDescription(const std::string& id) const {
    if (!m_artifactsData.contains(id)) {
        return "";
    }
    return UTF8to1251(m_artifactsData[id]["description"]);
}

int DataManager::GetArtifactPrice(const std::string& id) const {
    if (!m_artifactsData.contains(id)) {
        return 0;
    }
    return m_artifactsData[id]["price"];
}

void DataManager::LoadSpells(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть " << filepath << std::endl;
        return;
    }
    file >> m_spellsData;
    file.close();
}

std::string DataManager::GetSpellName(const std::string& id) const {
    if (!m_spellsData.contains(id)) return "Неизвестно";
    return UTF8to1251(m_spellsData[id]["name"]);
}

int DataManager::GetSpellMana(const std::string& id) const {
    if (!m_spellsData.contains(id)) return 0;
    return m_spellsData[id]["mana"];
}

std::vector<std::string> DataManager::GetRandomArtifactIdsExcluding(int count, const std::vector<std::string>& exclude) const {
    std::vector<std::string> ids;

    // Собрать все ID, кроме уже имеющихся
    for (auto& item : m_artifactsData.items()) {
        std::string id = item.key();
        bool isExcluded = false;
        for (auto& ex : exclude) {
            if (id == ex) {
                isExcluded = true;
                break;
            }
        }
        if (!isExcluded) {
            ids.push_back(id);
        }
    }

    // Если доступных меньше чем count — вернуть сколько есть
    if (ids.empty()) return {};

    // Перемешать
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ids.begin(), ids.end(), g);

    int resultSize = (count < (int)ids.size()) ? count : (int)ids.size();
    return std::vector<std::string>(ids.begin(), ids.begin() + resultSize);
}