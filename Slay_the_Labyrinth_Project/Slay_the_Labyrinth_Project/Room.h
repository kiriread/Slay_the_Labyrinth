#pragma once

#include <string>

enum class RoomType { REST, SHOP, MONSTER, ELITE, BOSS };

class Player;

class Room {
 protected:
  RoomType m_type;
  std::string m_description;
  std::string m_resultText;

 public:
  Room(RoomType type);
  virtual ~Room();

  RoomType GetType() const;
  std::string GetDescription() const;

  virtual void OnEnter(Player* player) = 0;

  void SetDescription(const std::string& desc);

  std::string GetResultText() const { return m_resultText; }
};
