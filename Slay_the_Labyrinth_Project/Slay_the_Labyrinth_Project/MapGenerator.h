#pragma once

#include <vector>
#include "Room.h"

class MapGenerator {
public:
	std::vector<RoomType> GenerateRoomOptions(int depth);
};