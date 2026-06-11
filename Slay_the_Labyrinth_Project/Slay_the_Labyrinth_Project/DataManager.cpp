#include "DataManager.h"

#include <windows.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>

// Загружаем классы из JSON
void DataManager::LoadClasses(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << GetString("Error") << filepath << std::endl;
    return;
  }
  file >> m_classData;
  file.close();
}

// Получаем статы класса по ID
Stats DataManager::GetClassStats(const std::string& classId) {
  Stats stats;

  if (!m_classData.contains(classId)) {
    std::cerr << GetString("ErrorClass") << classId << GetString("NotFound")
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

// Конвертация UTF-8 → Windows-1251 (для вывода в консоль)
std::string DataManager::UTF8to1251(const std::string& utf8) const {
    // Шаг 1: узнаём, сколько wide-символов понадобится
      // CP_UTF8 — исходная кодировка (UTF-8)
      // utf8.c_str() — исходная строка
      // -1 — строка заканчивается нулём
      // nullptr, 0 — не заполняем буфер, только узнаём размер
    int size = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);

    // Шаг 2: создаём wide-строку нужного размера
    std::wstring wtext(size, L'\0');

    // Шаг 3: конвертируем UTF-8 → Wide-строку (Unicode)
    // &wtext[0] — буфер для результата
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &wtext[0], size);

    // Шаг 4: узнаём, сколько байт понадобится в Windows-1251
    // 1251 — целевая кодовая страница
    int size1251 = WideCharToMultiByte(
        1251,            // целевая кодировка
        0,               // флаги (не используются)
        &wtext[0],       // исходная wide-строка
        -1,              // строка заканчивается нулём
        nullptr,         // не заполняем буфер
        0,               // размер буфера (0 = узнать размер)
        nullptr, nullptr // замена для недопустимых символов (не используется)
    );

    // Шаг 5: создаём обычную строку нужного размера
    std::string result(size1251, '\0');

    // Шаг 6: конвертируем Wide-строку → Windows-1251
    WideCharToMultiByte(
        1251,            // целевая кодировка
        0,               // флаги
        &wtext[0],       // исходная wide-строка
        -1,              // до нуля
        &result[0],      // буфер для результата
        size1251,        // размер буфера
        nullptr, nullptr // замена (не используется)
    );

    return result;  // Возвращаем строку в Windows-1251
}

// Русское название класса по ID
std::string DataManager::GetClassNamee(const std::string& classId) {
  if (!m_classData.contains(classId)) {
    return GetString("Unknown");
  }
  return UTF8to1251(m_classData[classId]["name"]);
}

// Список ID заклинаний класса
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

// Загружаем комнаты из JSON
void DataManager::LoadRooms(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << GetString("Error") << filepath << std::endl;
    return;
  }
  file >> m_roomData;
  file.close();
}

// Преобразование enum в строку-ключ для JSON
std::string DataManager::RoomTypeToString(RoomType type) {
  switch (type) {
    case RoomType::REST:
      return "REST";
    case RoomType::SHOP:
      return "SHOP";
    case RoomType::MONSTER:
      return "MONSTER";
    case RoomType::ELITE:
      return "ELITE";
    case RoomType::BOSS:
      return "BOSS";
    default:
      return "";
  }
}

// Русское название комнаты
std::string DataManager::GetRoomName(RoomType type) {
  std::string key = RoomTypeToString(type);
  return UTF8to1251(m_roomData["room_names"][key]);
}

// Описание комнаты
std::string DataManager::GetRoomDescription(RoomType type) {
  std::string key = RoomTypeToString(type);
  return UTF8to1251(m_roomData["room_descriptions"][key]);
}

// Загружаем игровые строки (интерфейс)
void DataManager::LoadStrings(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << GetString("Error") << filepath << std::endl;
    return;
  }
  file >> m_stringsData;
  file.close();
}

// Получаем строку по ключу
std::string DataManager::GetString(const std::string& key) {
  if (!m_stringsData.contains(key)) return "";
  return UTF8to1251(m_stringsData[key]);
}

// Загружаем артефакты из JSON
void DataManager::LoadArtifacts(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << GetString("Error") << filepath << std::endl;
    return;
  }
  file >> m_artifactsData;
  file.close();
}

// Русское название артефакта
std::string DataManager::GetArtifactName(const std::string& id) {
  if (!m_artifactsData.contains(id)) {
    return GetString("Unknown");
  }
  return UTF8to1251(m_artifactsData[id]["name"]);
}

// Описание артефакта
std::string DataManager::GetArtifactDescription(const std::string& id) const {
  if (!m_artifactsData.contains(id)) {
    return "";
  }
  return UTF8to1251(m_artifactsData[id]["description"]);
}

// Цена артефакта
int DataManager::GetArtifactPrice(const std::string& id) const {
  if (!m_artifactsData.contains(id)) {
    return 0;
  }
  return m_artifactsData[id]["price"];
}

// Загружаем заклинания из JSON
void DataManager::LoadSpells(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << GetString("Error") << filepath << std::endl;
    return;
  }
  file >> m_spellsData;
  file.close();
}

// Русское название заклинания
std::string DataManager::GetSpellName(const std::string& id) {
  if (!m_spellsData.contains(id)) return GetString("Unknown");
  return UTF8to1251(m_spellsData[id]["name"]);
}

// Стоимость заклинания в мане
int DataManager::GetSpellMana(const std::string& id) const {
  if (!m_spellsData.contains(id)) return 0;
  return m_spellsData[id]["mana"];
}

// Случайные ID артефактов, исключая уже имеющиеся у игрока
std::vector<std::string> DataManager::GetRandomArtifactIdsExcluding(
    int count, const std::vector<std::string>& exclude) const {
  std::vector<std::string> ids;

  // Собираем все ID, кроме тех, что уже в инвентаре
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

  // Если ничего доступного нет — возвращаем пустой вектор
  if (ids.empty()) return {};

  // Перемешать случайно
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(ids.begin(), ids.end(), g);

  // Сколько вернуть: запрошенное количество или сколько есть (меньшее из двух)
  int resultSize;
  if (count < (int)ids.size()) {
      resultSize = count;                 // Вернуть сколько просили
  }
  else {
      resultSize = (int)ids.size();       // Вернуть всё что есть
  }

  // Возвращаем первые resultSize элементов из перемешанного списка
  return std::vector<std::string>(ids.begin(), ids.begin() + resultSize);
}
