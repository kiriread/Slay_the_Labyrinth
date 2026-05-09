#pragma once

#include <string>
#include <vector>
#include "json.hpp"  
#include "Stats.h"

class DataManager {
private:
    nlohmann::json m_classData;
    std::string UTF8to1251(const std::string& utf8);

public:
    void LoadClasses(const std::string& filepath);
    Stats GetClassStats(const std::string& classId);
    std::string GetClassNamee(const std::string& classId);
    std::vector<std::string> GetClassSpells(const std::string& classId);
};