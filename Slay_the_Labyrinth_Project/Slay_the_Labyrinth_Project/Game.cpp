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
    m_console.Print(1, 1, m_dataManager.GetString("intro_line1"));
    m_console.Print(1, 2, m_dataManager.GetString("intro_line2"));
    m_console.Print(1, 5, m_dataManager.GetString("choose_class"));

    // Draw class options with arrow indicator
    for (int i = 0; i < 3; i++) {
      std::string name = m_dataManager.GetClassNamee(ids[i]);
      if (i == choice) {
        m_console.Print(2, 7 + i, "> " + name);  // Highlighted
      } else {
        m_console.Print(2, 7 + i, "  " + name);  // Normal
      }
    }

    /*m_console.Print(1, 11, m_dataManager.GetString("rules"));*/
    m_console.Print(1, 12, m_dataManager.GetString("continueEnter"));
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

void Game::RoomChoice() {
  m_roomOptions = m_mapGenerator.GenerateRoomOptions(m_currentCount);
  int choice = 0;
  int maxChoice = (int)m_roomOptions.size() - 1;

  while (true) {
    m_console.ClearScreen();
    HUD(60);

    m_console.Print(1, 1,
                    m_dataManager.GetString("count_label") + " " +
                        std::to_string(m_currentCount) + "/10");
    m_console.Print(1, 2, m_dataManager.GetString("choose_room"));

    for (int i = 0; i < m_roomOptions.size(); i++) {
      std::string name = m_dataManager.GetRoomName(m_roomOptions[i]);
      if (i == choice) {
        m_console.Print(2, 4 + i, "> " + name);
      } else {
        m_console.Print(2, 4 + i, "  " + name);
      }
    }

    /*m_console.Print(1, 11, m_dataManager.GetString("continueEnter"));*/
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
      room = new ShopRoom(&m_dataManager, &m_console, this);
      break;
    case RoomType::MONSTER:
      room = new MonsterRoom(this);
      break;
    case RoomType::ELITE:
      room = new EliteRoom(this);
      break;
    case RoomType::BOSS:
      room = new BossRoom(this);
      break;
  }

  if (room != nullptr) {
    room->SetDescription(m_dataManager.GetRoomDescription(type));

    m_console.ClearScreen();
    HUD(60);

    if (type != RoomType::SHOP) {
      m_console.Print(1, 1, room->GetDescription());
    }

    room->OnEnter(m_player);

    if (type == RoomType::SHOP) {
      m_console.ClearScreen();
      HUD(60);
    }

    int total_x = 1;
    /*m_console.Print(total_x, 1, m_dataManager.GetString("separator"));*/
    m_console.Print(total_x, 1, m_dataManager.GetString("total"));
    m_console.Print(total_x, 2, room->GetResultText());
    /*m_console.Print(total_x, 4, m_dataManager.GetString("separator"));*/
    /*m_console.Print(total_x, 11, m_dataManager.GetString("continue"));*/
    m_console.GetKey();

    delete room;
    m_currentCount++;
  }
}

void Game::HUD(int x) {
  m_console.Print(
      x, 1,
      m_dataManager.GetString("your_class") + " " + m_player->GetClassName());

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
  m_console.Print(x, 5,
                  m_dataManager.GetString("gld_label") +
                      std::to_string(m_player->GetGold()));

  m_console.Print(x, 6, m_dataManager.GetString("separator"));

  auto spells = m_dataManager.GetClassSpells(m_player->GetClassName());
  std::string spellsText = m_dataManager.GetString("spells_label");
  for (size_t i = 0; i < spells.size(); i++) {
    spellsText += spells[i];
    if (i < spells.size() - 1) spellsText += ", ";
  }
  m_console.Print(x, 7, spellsText);

  std::string artifactsTitle = m_dataManager.GetString("artifacts_label");
  auto& inventory = m_player->GetInventory();

  if (inventory.empty()) {
    m_console.Print(x, 8, artifactsTitle);
    m_console.Print(x, 9, m_dataManager.GetString("separator"));
  } else {
    m_console.Print(x, 8, artifactsTitle);

    int line = 9;
    for (size_t i = 0; i < inventory.size(); i++) {
      std::string name = m_dataManager.GetArtifactName(inventory[i]);
      m_console.Print(x, line, "  " + name);
      line++;
    }

    m_console.Print(x, line, m_dataManager.GetString("separator"));
  }
}
