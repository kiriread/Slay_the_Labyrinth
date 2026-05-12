#include "ShopRoom.h"

#include "Player.h"

ShopRoom::ShopRoom(DataManager* dm, ConsoleUtils* console)
    : Room(RoomType::SHOP),
      m_dataManager(dm),
      m_console(console),
      m_priceMultiplier(1.0f) {}

void ShopRoom::OnEnter(Player* player) {
  m_stock = m_dataManager->GetRandomArtifactIds(3);
  m_priceMultiplier = 1.0f;

  int choice = 0;
  int maxChoice = (int)m_stock.size() - 1;

  while (true) {
    m_console->Print(0, 2, m_dataManager->GetString("shop_title"));

    for (int i = 0; i < (int)m_stock.size(); i++) {
      std::string name = m_dataManager->GetArtifactName(m_stock[i]);
      std::string desc = m_dataManager->GetArtifactDescription(m_stock[i]);
      int basePrice = m_dataManager->GetArtifactPrice(m_stock[i]);
      int finalPrice = (int)(basePrice * m_priceMultiplier);

      std::string line;
      if (i == choice) {
        line = "> ";
      } else {
        line = "  ";
      }
      line += name + " — " + std::to_string(finalPrice) +
              m_dataManager->GetString("shop_gold_suffix");

      m_console->Print(0, 4 + i * 3, line);
      m_console->Print(2, 5 + i * 3, desc);
    }

    m_console->Print(0, 13, m_dataManager->GetString("shop_price_hint"));
    m_console->Print(0, 15, m_dataManager->GetString("shopContinue"));

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
      int basePrice = m_dataManager->GetArtifactPrice(m_stock[choice]);
      int finalPrice = (int)(basePrice * m_priceMultiplier);

      if (player->SpendGold(finalPrice)) {
        player->AddArtifact(m_stock[choice]);
        m_resultText = m_dataManager->GetString("shop_purchased") +
                       m_dataManager->GetArtifactName(m_stock[choice]);
        m_priceMultiplier += 0.5f;
      } else {
        m_resultText = m_dataManager->GetString("shop_not_enough_gold");
      }
    }

    if (key == 27) {
      if (m_resultText.empty()) {
        m_resultText = m_dataManager->GetString("shop_leave");
      }
      break;
    }
  }
}
