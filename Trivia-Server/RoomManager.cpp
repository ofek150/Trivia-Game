#include "RoomManager.h"


void RoomManager::createRoom(const LoggedUser& user, const RoomData& roomData)
{
	if (roomData.maxPlayers < 2 || roomData.maxPlayers > 5) throw std::exception("Max players has be between 2 and 5.");
	if (roomData.numOfQuestionsInGame < 1 || roomData.numOfQuestionsInGame > 40) throw std::exception("The number of questions has to be between 1 and 40.");
	if (roomData.timePerQuestion < 1 || roomData.timePerQuestion > 120) throw std::exception("The time for each question has to be between 1 and 120 seconds.");
	if (roomData.name.length() <= 2) throw std::exception("The room's name has to be at least 2 characters long.");
	for (const auto& room : m_rooms)
	{
		if(room.second.getRoomData().name == roomData.name) throw std::exception("The room's name is already taken.");
	}

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
