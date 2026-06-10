#include "Game.h"

Game::Game() : m_isRunning(false), m_player(nullptr) {
  m_dataManager.LoadClasses("assets/json/classes.json");
  m_dataManager.LoadRooms("assets/json/rooms.json");
  m_dataManager.LoadStrings("assets/json/strings.json");
  m_dataManager.LoadArtifacts("assets/json/artifacts.json");
  m_dataManager.LoadSpells("assets/json/spells.json");
  m_currentCount = 1;
}

Game::~Game() { delete m_player; }

void Game::Run() {
  MainMenu();

  while (m_isRunning) {
    m_console.WaitForEnter(); // Ждём Enter перед выбором комнаты
    RoomChoice();
  }
}

// Меню выбора класса
void Game::MainMenu() {
  std::string ids[3] = {"warrior", "rogue", "mage"};
  int choice = 0; 
  int maxChoice = 2;

  while (true) {
    m_console.ClearScreen();

    // Вступительный текст
    m_console.Print(1, 1, m_dataManager.GetString("intro_line1"));
    m_console.Print(1, 2, m_dataManager.GetString("intro_line2"));
    m_console.Print(1, 5, m_dataManager.GetString("choose_class"));

    // Вывод трёх классов с подсветкой выбранного
    for (int i = 0; i < 3; i++) {
      std::string name = m_dataManager.GetClassNamee(ids[i]);
      if (i == choice) {
        m_console.Print(2, 7 + i, "> " + name);  // Выбранный
      } else {
        m_console.Print(2, 7 + i, "  " + name);  // Остальные
      }
    }

    m_console.Print(1, 12, m_dataManager.GetString("continueEnter"));
    int key = m_console.GetKey();

    // Обработка стрелок 
    if (key == 224) { // маркер «это спец-клавиша», потому что стрелки - 2 байта
      key = m_console.GetKey();  
      if (key == 72) {           // Стрелка Вверх
        choice--;
        if (choice < 0) choice = 2;  
      }
      if (key == 80) {  // Стрелка Вниз
        choice++;
        if (choice > maxChoice)     // Если ушли ниже последнего 
            choice = 0;     // Вернуться на первый 
      }
    }

    // Enter — подтвердить выбор
    if (key == 13) {
      break;  
    }
  }

  // Создаём игрока по выбранному классу
  std::string classId = ids[choice];
  Stats stats = m_dataManager.GetClassStats(classId);
  std::string className = m_dataManager.GetClassNamee(classId);
  m_player = new Player(classId, className, stats);
  m_isRunning = true;
}

void Game::RoomChoice() {
  if (m_currentCount == 10) {
    EnterRoom(RoomType::BOSS);
  }
  else {
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
              }
              else {
                  m_console.Print(2, 4 + i, "  " + name);
              }
          }

          int key = m_console.GetKey();

          // Обработка стрелок
          if (key == 224) { // маркер «это спец-клавиша», потому что стрелки - 2 байта
              key = m_console.GetKey();
              if (key == 72) { // Стрелка Вверх
                  choice--;
                  if (choice < 0) choice = maxChoice;
              }
              if (key == 80) { // Стрелка Вниз
                  choice++;
                  if (choice > maxChoice) choice = 0;
              }
          }

          // Enter — войти в выбранную комнату
          if (key == 13) {
              break;
          }
      }

      EnterRoom(m_roomOptions[choice]);
  }

}

// Вход в комнату и обработка её действия
void Game::EnterRoom(RoomType type) {
  Room* room = nullptr;

  // Создаём комнату нужного типа
  switch (type) {
    case RoomType::REST:
      room = new RestRoom(&m_dataManager, this);
      break;
    case RoomType::SHOP:
      room = new ShopRoom(&m_dataManager, &m_console, this);
      break;
    case RoomType::MONSTER:
        room = new MonsterRoom(this, &m_dataManager, &m_console);
        break;
    case RoomType::ELITE:
        room = new EliteRoom(this, &m_dataManager, &m_console);
        break;
    case RoomType::BOSS:
        room = new BossRoom(this, &m_dataManager, &m_console);
        break;
  }

  if (room != nullptr) {
    room->SetDescription(m_dataManager.GetRoomDescription(type));

    // Для всех комнат, кроме торговца: показать описание и ждать Enter
    if (type != RoomType::SHOP) {
      m_console.ClearScreen();
      HUD(60);
      m_console.Print(1, 1, room->GetDescription());
      m_console.WaitForEnter();
    }

    // Действие комнаты (бой, отдых, покупка)
    room->OnEnter(m_player);

    // Показываем результат
    m_console.ClearScreen();
    HUD(60);

    int total_x = 1;
    m_console.Print(total_x, 1, m_dataManager.GetString("total"));
    m_console.Print(total_x, 2, room->GetResultText());
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

  // Заклинания
  // Получаем список ID заклинаний класса игрока
  auto spells = m_dataManager.GetClassSpells(m_player->GetClassId());
  m_console.Print(x, 7, m_dataManager.GetString("spells_label"));

  int line = 8; 
  for (size_t i = 0; i < spells.size(); i++) {
      // По ID получаем русское название
      std::string spellName = m_dataManager.GetSpellName(spells[i]);
      // По ID получаем стоимость
      int mana = m_dataManager.GetSpellMana(spells[i]);
      m_console.Print(x, line, "  " + spellName + " - " + std::to_string(mana) + " MP");
      line++;  // Следующая строка
  }

  // Артефакты
  // Получаем инвентарь игрока (вектор ID артефактов)
  auto& inventory = m_player->GetInventory();
  std::string artifactsTitle = m_dataManager.GetString("artifacts_label");

  if (inventory.empty()) {
    m_console.Print(x, 11, artifactsTitle);
    m_console.Print(x, 12, m_dataManager.GetString("separator"));
  } else {
    m_console.Print(x, 11, artifactsTitle);

    int line = 12;
    for (size_t i = 0; i < inventory.size(); i++) {
        // По ID получаем русское название
        std::string name = m_dataManager.GetArtifactName(inventory[i]);
        m_console.Print(x, line, "  " + name);
        line++;  // Следующая строка
    }

    m_console.Print(x, line, m_dataManager.GetString("separator"));
  }
}
