#include "Room.h"

Room::Room(RoomType type) : m_type(type) {}

Room::~Room() = default;

std::string Room::GetDescription() const {
    return m_description;
}

void Room::SetDescription(const std::string& desc) {
    m_description = desc;
}
