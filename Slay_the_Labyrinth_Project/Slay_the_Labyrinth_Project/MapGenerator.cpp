#include "MapGenerator.h"

#include <algorithm>
#include <random>

std::vector<RoomType> MapGenerator::GenerateRoomOptions(int count) {
  std::vector<RoomType> pool = {RoomType::REST, RoomType::SHOP,
                                RoomType::MONSTER, RoomType::ELITE};

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(pool.begin(), pool.end(), g);

  // Возвращаем первые три
  return std::vector<RoomType>(pool.begin(), pool.begin() + 3);
}
