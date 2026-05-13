#include "MapGenerator.h"

#include <algorithm>
#include <random>

std::vector<RoomType> MapGenerator::GenerateRoomOptions(int depth) {
  // All possible room types (except BOSS)
  std::vector<RoomType> pool = {RoomType::REST, RoomType::SHOP,
                                RoomType::MONSTER, RoomType::ELITE};

  // Shuffle pool randomly
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(pool.begin(), pool.end(), g);

  // Return first 3
  return std::vector<RoomType>(pool.begin(), pool.begin() + 3);
}
