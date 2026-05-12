#include "Game.h"

Game::Game() : m_isRunning(false), m_player(nullptr) {
  m_dataManager.LoadClasses("assets/json/classes.json");
  m_dataManager.LoadRooms("assets/json/rooms.json");
  m_dataManager.LoadStrings("assets/json/strings.json");
  m_dataManager.LoadArtifacts("assets/json/artifacts.json");
  m_currentCount = 1;
}

Game::~Game() { delete m_player; }

void Game::Run() {
  MainMenu();
  /*YourChoice();*/

  while (m_isRunning) {
    int key = m_console.GetKey();
    /*ProcessInput(key);*/
    RoomChoice();
  }
}

void Game::MainMenu() {
  // Class IDs matching the JSON keys
  std::string ids[3] = {"warrior", "rogue", "mage"};
  int choice = 0;  // Index of the currently selected class

  while (true) {
    m_console.ClearScreen();

    // Draw menu header
    m_console.Print(0, 1, m_dataManager.GetString("intro_line1"));
    m_console.Print(0, 2, m_dataManager.GetString("intro_line2"));
    m_console.Print(0, 5, m_dataManager.GetString("choose_class"));

    // Draw class options with arrow indicator
    for (int i = 0; i < 3; i++) {
      std::string name = m_dataManager.GetClassNamee(ids[i]);
      if (i == choice) {
        m_console.Print(1, 7 + i, "> " + name);  // Highlighted
      } else {
        m_console.Print(1, 7 + i, "  " + name);  // Normal
      }
    }

    m_console.Print(0, 11, m_dataManager.GetString("continueEnter"));
    int key = m_console.GetKey();

    // Handle arrow keys (two-code escape sequence)
    if (key == 224) {
      key = m_console.GetKey();  // Read direction code
      if (key == 72) {           // Up arrow
        choice--;
        if (choice < 0) choice = 2;  // Wrap around to bottom
      }
      if (key == 80) {  // Down arrow
        choice++;
        if (choice > 2) choice = 0;  // Wrap around to top
      }
    }

    // Enter key — confirm selection
    if (key == 13) {
      break;  // Exit menu loop
    }
  }

  // Create the player based on selected class
  std::string classId = ids[choice];
  Stats stats = m_dataManager.GetClassStats(classId);
  std::string name = m_dataManager.GetClassNamee(classId);
  m_player = new Player(name, stats);
  m_isRunning = true;
}

// void Game::YourChoice() {
//   m_console.ClearScreen();
//
//   // Player class
//   m_console.Print(
//       0, 0, m_dataManager.GetString("your_class") +
//       m_player->GetClassName());
//
//   // Stats
//   m_console.Print(0, 2,
//                   m_dataManager.GetString("hp_label") +
//                       std::to_string(m_player->GetCurrentHP()) + " / " +
//                       std::to_string(m_player->GetMaxHP()));
//   m_console.Print(0, 3,
//                   m_dataManager.GetString("mp_label") +
//                       std::to_string(m_player->GetCurrentMP()) + " / " +
//                       std::to_string(m_player->GetMaxMP()));
//   m_console.Print(0, 4,
//                   m_dataManager.GetString("atk_label") +
//                       std::to_string(m_player->GetATK()));
//   m_console.Print(0, 5,
//                   m_dataManager.GetString("spd_label") +
//                       std::to_string(m_player->GetSPD()));
//   m_console.Print(0, 6,
//                   m_dataManager.GetString("int_label") +
//                       std::to_string(m_player->GetINT()));
//
//   m_console.Print(0, 8, m_dataManager.GetString("continue"));
// }

// void Game::ProcessInput(int key) {
// }

void Game::RoomChoice() {
  m_roomOptions = m_mapGenerator.GenerateRoomOptions(m_currentCount);
  int choice = 0;
  int maxChoice = (int)m_roomOptions.size() - 1;

  while (true) {
    m_console.ClearScreen();
    HUD();

    m_console.Print(0, 1,
                    m_dataManager.GetString("count_label") + " " +
                        std::to_string(m_currentCount) + "/10");
    m_console.Print(0, 2, m_dataManager.GetString("choose_room"));

    for (int i = 0; i < m_roomOptions.size(); i++) {
      std::string name = m_dataManager.GetRoomName(m_roomOptions[i]);
      if (i == choice) {
        m_console.Print(1, 4 + i, "> " + name);
      } else {
        m_console.Print(1, 4 + i, "  " + name);
      }
    }

    m_console.Print(0, 11, m_dataManager.GetString("continueEnter"));
    int key = m_console.GetKey();

    if (key == 224) {
      key = m_console.GetKey();
      if (key == 72) {
        choice--;
        if (choice < 0) choice = maxChoice;
      }
      if (key == 80) {
        choice++;
        if (choice > maxChoice) choice = 0;
      }
    }

    if (key == 13) {
      break;
    }
  }

  EnterRoom(m_roomOptions[choice]);
}

void Game::EnterRoom(RoomType type) {
  Room* room = nullptr;

  switch (type) {
    case RoomType::REST:
      room = new RestRoom();
      break;
    case RoomType::SHOP:
      room = new ShopRoom();
      break;
    case RoomType::MONSTER:
      room = new MonsterRoom();
      break;
    case RoomType::ELITE:
      room = new EliteRoom();
      break;
    case RoomType::BOSS:
      room = new BossRoom();
      break;
  }

  if (room != nullptr) {
    room->SetDescription(m_dataManager.GetRoomDescription(type));
    room->OnEnter(m_player);

    m_console.ClearScreen();
    HUD();
    m_console.Print(0, 1, room->GetDescription());
    m_console.Print(0, 3, room->GetResultText());
    m_console.Print(0, 11, m_dataManager.GetString("continue"));
    m_console.GetKey();

    delete room;
    m_currentCount++;
  }
}

void Game::HUD() {
  int x = 60;
  // Класс игрока
  m_console.Print(
      x, 1,
      m_dataManager.GetString("your_class") + " " + m_player->GetClassName());

  // Характеристики
  m_console.Print(x, 2,
                  m_dataManager.GetString("hp_label") +
                      std::to_string(m_player->GetCurrentHP()) + " / " +
                      std::to_string(m_player->GetMaxHP()));
  m_console.Print(x, 3,
                  m_dataManager.GetString("mp_label") +
                      std::to_string(m_player->GetCurrentMP()) + " / " +
                      std::to_string(m_player->GetMaxMP()));
  m_console.Print(x, 4,
                  m_dataManager.GetString("atk_label") +
                      std::to_string(m_player->GetATK()) + "  " +
                      m_dataManager.GetString("spd_label") +
                      std::to_string(m_player->GetSPD()) + "  " +
                      m_dataManager.GetString("int_label") +
                      std::to_string(m_player->GetINT()));
  m_console.Print(x, 5, "GLD: " /*+ std::to_string(m_player->GetGold())*/);

  // Разделитель
  m_console.Print(x, 6, "--------------------------");

  // Способности
  auto spells = m_dataManager.GetClassSpells(m_player->GetClassName());
  std::string spellsText = "Способности: ";
  for (size_t i = 0; i < spells.size(); i++) {
    spellsText += spells[i];
    if (i < spells.size() - 1) spellsText += ", ";
  }
  m_console.Print(x, 7, spellsText);

  //// Артефакты
  // std::string artifactsText = "Артефакты: ";
  // auto& inventory = m_player->GetInventory();
  // if (inventory.empty()) {
  //     artifactsText += "(нет)";
  // }
  // else {
  //     for (size_t i = 0; i < inventory.size(); i++) {
  //         artifactsText += m_dataManager.GetArtifactName(inventory[i]);
  //         if (i < inventory.size() - 1) artifactsText += ", ";
  //     }
  // }
  m_console.Print(x, 8, "Артефакты: ");

  // Разделитель
  m_console.Print(x, 9, "--------------------------");
}
