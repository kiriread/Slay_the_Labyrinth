#pragma once
#include "Room.h"
#include "DataManager.h"
#include "ConsoleUtils.h"
#include <vector>
#include <string>

class ShopRoom : public Room {
private:
    std::vector<std::string> m_stock;     // 3 случайных ID артефактов
    float m_priceMultiplier;              // Множитель цены (1.0 → 1.5 → 2.25)
    DataManager* m_dataManager;           // Указатель на DataManager
    ConsoleUtils* m_console;              // Указатель на консоль

public:
    ShopRoom(DataManager* dm, ConsoleUtils* console);
    void OnEnter(Player* player) override;
};