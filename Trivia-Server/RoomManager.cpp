#include "RoomManager.h"


void RoomManager::createRoom(const LoggedUser& user, const RoomData& roomData)
{
	Room newRoom(user, roomData);
	newRoom.addUser(user);
	m_rooms.emplace(roomData.id, newRoom);
}

void RoomManager::deleteRoom(unsigned int ID)
{
	auto it = m_rooms.find(ID);
	//Notify users to leave room
	if (it != m_rooms.end()) m_rooms.erase(it);
}

void RoomManager::JoinRoom(const LoggedUser& user, unsigned int ID)
{
	auto it = m_rooms.find(ID);
	if (it == m_rooms.end()) throw std::exception("Invalid Room id!");
	if (it->second.getRoomState()) throw std::exception("Game already started!");
	it->second.addUser(user);
}

unsigned int RoomManager::getRoomState(unsigned int ID) const
{
	auto it = m_rooms.find(ID);
	if (it != m_rooms.end()) return it->second.getRoomState();
}

std::map<unsigned int, Room>* RoomManager::getRooms()
{
	return &m_rooms;
}

const std::vector<RoomData> RoomManager::getRoomsDatas() const
{
	std::vector<RoomData> rooms;
	for (auto room : m_rooms)
		rooms.push_back(room.second.getRoomData());

	return rooms;
}

const Room& RoomManager::getRoom(unsigned int ID) const
{
	return m_rooms.at(ID);
}
