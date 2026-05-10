#pragma once

#include <string>
#include <vector>
#include "json.hpp"  
#include "Stats.h"
#include "Room.h"

class DataManager {
private:
    nlohmann::json m_classData;
    nlohmann::json m_roomData;
    nlohmann::json m_stringsData;
    std::string UTF8to1251(const std::string& utf8);

public:
    // Classes
    void LoadClasses(const std::string& filepath);
    Stats GetClassStats(const std::string& classId);
    std::string GetClassNamee(const std::string& classId);
    std::vector<std::string> GetClassSpells(const std::string& classId);

    // Rooms
    void LoadRooms(const std::string& filepath);
    std::string GetRoomName(RoomType type);
    std::string GetRoomDescription(RoomType type);
    std::string RoomTypeToString(RoomType type);

    // Strings
    void LoadStrings(const std::string& filepath);
    std::string GetString(const std::string& key);
};