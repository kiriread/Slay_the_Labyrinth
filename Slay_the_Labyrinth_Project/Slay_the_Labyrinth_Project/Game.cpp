#include "Game.h"

Game::Game() : m_isRunning(false), m_player(nullptr) {
  m_dataManager.LoadClasses("assets/json/classes.json");
  m_dataManager.LoadRooms("assets/json/rooms.json");
  m_dataManager.LoadStrings("assets/json/strings.json");
  m_currentCount = 1;
}

Game::~Game() { delete m_player; }

void Game::Run() {
  ShowMainMenu();
  Render();

  while (m_isRunning) {
    int key = m_console.GetKey();
    /*ProcessInput(key);*/
    ShowRoomChoice();
  }
}

void Game::ShowMainMenu() {
  // Class IDs matching the JSON keys
  std::string ids[3] = {"warrior", "rogue", "mage"};
  int choice = 0;  // Index of the currently selected class

  while (true) {
    m_console.ClearScreen();

    // Draw menu header
    m_console.Print(0, 0, m_dataManager.GetString("intro_line1"));
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

void Game::Render() {
  m_console.ClearScreen();

  // Player class
  m_console.Print(
      0, 0, m_dataManager.GetString("your_class") + m_player->GetClassName());

  // Stats
  m_console.Print(0, 2,
                  m_dataManager.GetString("hp_label") +
                      std::to_string(m_player->GetCurrentHP()) + " / " +
                      std::to_string(m_player->GetMaxHP()));
  m_console.Print(0, 3,
                  m_dataManager.GetString("mp_label") +
                      std::to_string(m_player->GetCurrentMP()) + " / " +
                      std::to_string(m_player->GetMaxMP()));
  m_console.Print(0, 4,
                  m_dataManager.GetString("atk_label") +
                      std::to_string(m_player->GetATK()));
  m_console.Print(0, 5,
                  m_dataManager.GetString("spd_label") +
                      std::to_string(m_player->GetSPD()));
  m_console.Print(0, 6,
                  m_dataManager.GetString("int_label") +
                      std::to_string(m_player->GetINT()));

  m_console.Print(0, 8, m_dataManager.GetString("continue"));
}

void Game::ProcessInput(int key) {
  // Future(ESC?)
}

void Game::ShowRoomChoice() {
  m_roomOptions = m_mapGenerator.GenerateRoomOptions(m_currentCount);
  int choice = 0;
  int maxChoice = (int)m_roomOptions.size() - 1;

  while (true) {
    m_console.ClearScreen();

    m_console.Print(0, 0,
                    m_dataManager.GetString("count_label") + " " +
                        std::to_string(m_currentCount) + "/10");
    m_console.Print(0, 2, m_dataManager.GetString("choose_room"));

    for (int i = 0; i < m_roomOptions.size(); i++) {
      std::string name = m_dataManager.GetRoomName(m_roomOptions[i]);
      if (i == choice) {
        m_console.Print(1, 3 + i, "> " + name);
      } else {
        m_console.Print(1, 3 + i, "  " + name);
      }
    }

    m_console.Print(0, 7, m_dataManager.GetString("continueEnter"));
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

    m_console.ClearScreen();
    m_console.Print(0, 0, room->GetDescription());
    room->OnEnter(m_player);
    m_console.Print(0, 2, room->GetResultText());
    m_console.Print(0, 4, m_dataManager.GetString("continue"));
    m_console.GetKey();

    delete room;
    m_currentCount++;
  }
}
