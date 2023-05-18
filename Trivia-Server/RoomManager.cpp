#include "RoomManager.h"


void RoomManager::createRoom(const LoggedUser& user, const RoomData& roomData)
{
	Room newRoom(roomData);
	newRoom.addUser(user);
}

void RoomManager::deleteRoom(unsigned int ID)
{
	auto it = m_rooms.find(ID);
	if (it != m_rooms.end()) m_rooms.erase(it);
}

unsigned int RoomManager::getRoomState(unsigned int ID) const
{
	auto it = m_rooms.find(ID);
	if (it != m_rooms.end()) return it->second.getRoomState();
}

const std::map<unsigned int, Room>& RoomManager::getRooms() const
{
	return m_rooms;
}

const Room& RoomManager::getRoom(unsigned int ID) const
{
	return m_rooms.at(ID);
}
