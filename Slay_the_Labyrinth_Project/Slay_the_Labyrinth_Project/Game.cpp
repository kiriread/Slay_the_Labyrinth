#include "Game.h"

Game::Game() : m_isRunning(false), m_player(nullptr) {
  m_dataManager.LoadClasses("assets/json/classes.json");
}

Game::~Game() { delete m_player; }

void Game::Run() {
  ShowMainMenu();

  while (m_isRunning) {
    Render();
    int key = m_console.GetKey();
    ProcessInput(key);
  }
}

void Game::ShowMainMenu() {
  // Class IDs matching the JSON keys
  std::string ids[3] = {"warrior", "rogue", "mage"};
  int choice = 0;  // Index of the currently selected class

  while (true) {
    m_console.ClearScreen();

    // Draw menu header
    m_console.Print(0, 0,
                    "¬ы просыпаетесь в темной сырой комнате, совершенно "
                    "позабыв кто вы и почему тут находитесь.");
    m_console.Print(0, 2, "¬спомните кто вы:");

    // Draw class options with arrow indicator
    for (int i = 0; i < 3; i++) {
      std::string name = m_dataManager.GetClassNamee(ids[i]);
      if (i == choice) {
        m_console.Print(1, 4 + i, "> " + name);  // Highlighted
      } else {
        m_console.Print(1, 4 + i, "  " + name);  // Normal
      }
    }

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

    // Enter key Ч confirm selection
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
  m_console.Print(0, 0, "¬аш класс: " + m_player->GetClassName());

  // Stats
  m_console.Print(0, 2,
                  "HP:  " + std::to_string(m_player->GetCurrentHP()) + " / " +
                      std::to_string(m_player->GetMaxHP()));
  m_console.Print(0, 3,
                  "MP:  " + std::to_string(m_player->GetCurrentMP()) + " / " +
                      std::to_string(m_player->GetMaxMP()));
  m_console.Print(0, 4, "ATK: " + std::to_string(m_player->GetATK()));
  m_console.Print(0, 5, "SPD: " + std::to_string(m_player->GetSPD()));
  m_console.Print(0, 6, "INT: " + std::to_string(m_player->GetINT()));
}

void Game::ProcessInput(int key) {
  // Future
}
