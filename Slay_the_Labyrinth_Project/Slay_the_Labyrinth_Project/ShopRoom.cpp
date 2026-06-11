#include "ShopRoom.h"

#include "Game.h"
#include "Player.h"

ShopRoom::ShopRoom(DataManager* dm, ConsoleUtils* console, Game* game)
    : Room(RoomType::SHOP),
      m_dataManager(dm),
      m_console(console),
      m_game(game) {}

void ShopRoom::OnEnter(Player* player) {
  m_stock =
      m_dataManager->GetRandomArtifactIdsExcluding(3, player->GetInventory());

  // Если ВСЕ артефакты уже собраны — показать сообщение и ждать ESC
  if (m_stock.empty()) {
    while (true) {
      m_console->ClearScreen();
      m_game->HUD(70);
      m_console->Print(1, 1, m_dataManager->GetString("alt_description"));
      m_console->Print(1, 2, m_dataManager->GetString("shop_empty"));

      int key = m_console->GetKey();
      if (key == 27 or key == 13) {
        m_resultText = m_dataManager->GetString("shop_leave");
        return;
      }
    }
  }

  int choice = 0;
  std::string message = "";

  while (!m_stock.empty()) {
    int maxChoice = (int)m_stock.size() - 1;
    if (choice > maxChoice) choice = maxChoice;

    // Очистка и перерисовка (HUD + товары)
    m_console->ClearScreen();
    m_game->HUD(60);

    m_console->Print(1, 1, m_description);
    m_console->Print(1, 3, m_dataManager->GetString("shop_title"));

    // Вывод списка товаров
    for (int i = 0; i < (int)m_stock.size(); i++) {
      std::string name = m_dataManager->GetArtifactName(m_stock[i]);
      std::string desc = m_dataManager->GetArtifactDescription(m_stock[i]);
      int price = m_dataManager->GetArtifactPrice(m_stock[i]);

      if (player->HasArtifact("discount_coupon")) {
        price = price / 2;
      }

      // Подсветка выбранного товара стрелкой
      std::string line;
      if (i == choice)
        line = "> ";
      else
        line = "  ";
      line += name + " - " + std::to_string(price) +
              m_dataManager->GetString("shop_gold_suffix");

      m_console->Print(1, 5 + i * 3, line);  // Название и цена
      m_console->Print(3, 6 + i * 3, desc);  // Описание со сдвигом
    }

    // Показываем результат предыдущей покупки
    if (!message.empty()) {
      m_console->Print(1, 14, message);
    }

    int key = m_console->GetKey();

    // Навигация стрелками
    if (key == 224) {
      key = m_console->GetKey();
      if (key == 72) {  // Вверх
        choice--;
        if (choice < 0) choice = maxChoice;  // Зацикливание на последний
      }
      if (key == 80) {  // Вниз
        choice++;
        if (choice > maxChoice) choice = 0;  // Зацикливание на первый
      }
    }

    // Enter — покупк
    if (key == 13) {
      int price = m_dataManager->GetArtifactPrice(m_stock[choice]);

      // Проверяем скидку ещё раз (для списания золота)
      if (player->HasArtifact("discount_coupon")) {
        price = price / 2;
      }

      if (player->SpendGold(price)) {
        player->AddArtifact(m_stock[choice]);
        message = m_dataManager->GetString("shop_purchased") +
                  m_dataManager->GetArtifactName(m_stock[choice]);
        m_stock.erase(m_stock.begin() + choice);
      } else {
        message = m_dataManager->GetString("shop_not_enough_gold");
      }
    }

    // ESC — выход от торговца
    if (key == 27) {
      m_resultText = m_dataManager->GetString("shop_leave");
      break;
    }
  }

  if (m_stock.empty() && m_resultText.empty()) {
    m_resultText = m_dataManager->GetString("shop_all_buyed");
  }
}
