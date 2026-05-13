#include "ShopRoom.h"

#include "Game.h"
#include "Player.h"

ShopRoom::ShopRoom(DataManager* dm, ConsoleUtils* console, Game* game)
    : Room(RoomType::SHOP),
      m_dataManager(dm),
      m_console(console),
      m_game(game) {}

void ShopRoom::OnEnter(Player* player) {
  m_stock = m_dataManager->GetRandomArtifactIds(3);
  int choice = 0;
  std::string message = "";

  while (!m_stock.empty()) {
    int maxChoice = (int)m_stock.size() - 1;
    if (choice > maxChoice) choice = maxChoice;

    m_console->ClearScreen();
    m_game->HUD(80);

    // ÐžÐ¿Ð¸ÑÐ°Ð½Ð¸Ðµ Ð¸ Ñ‚Ð¾Ð²Ð°Ñ€Ñ‹
    m_console->Print(0, 1, m_description);
    m_console->Print(0, 3, m_dataManager->GetString("shop_title"));

    for (int i = 0; i < (int)m_stock.size(); i++) {
      std::string name = m_dataManager->GetArtifactName(m_stock[i]);
      std::string desc = m_dataManager->GetArtifactDescription(m_stock[i]);
      int price = m_dataManager->GetArtifactPrice(m_stock[i]);

      std::string line;
      if (i == choice)
        line = "> ";
      else
        line = "  ";
      line += name + " — " + std::to_string(price) +
              m_dataManager->GetString("shop_gold_suffix");

      m_console->Print(0, 5 + i * 3, line);
      m_console->Print(2, 6 + i * 3, desc);
    }

    // Ñîîáùåíèå
    if (!message.empty()) {
      m_console->Print(0, 18, message);
    }

    // Ïîäñêàçêà
    m_console->Print(0, 20, m_dataManager->GetString("shopContinue"));

    int key = m_console->GetKey();

    if (key == 224) {
      key = m_console->GetKey();
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
      int price = m_dataManager->GetArtifactPrice(m_stock[choice]);
      if (player->SpendGold(price)) {
        player->AddArtifact(m_stock[choice]);
        message = m_dataManager->GetString("shop_purchased") +
                  m_dataManager->GetArtifactName(m_stock[choice]);
        m_stock.erase(m_stock.begin() + choice);
      } else {
        message = m_dataManager->GetString("shop_not_enough_gold");
      }
    }

    if (key == 27) {
      m_resultText = m_dataManager->GetString("shop_leave");
      break;
    }
  }

  if (m_stock.empty() and m_resultText.empty()) {
    m_resultText = "Âñå òîâàðû ðàñïðîäàíû.";
  }
}
