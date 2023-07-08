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

	/*Room newRoom(user, roomData);
	newRoom.addUser(user);*/

	std::lock_guard<std::mutex> rooms_lock(rooms_mutex);
	m_rooms.emplace(roomData.id, Room(user, roomData));
	m_rooms.at(roomData.id).addUser(user);
	m_idCounter += 1;
}

void RoomManager::deleteRoom(unsigned int ID)
{
	std::lock_guard<std::mutex> rooms_lock(rooms_mutex);
	auto it = m_rooms.find(ID);
	if (it != m_rooms.end()) m_rooms.erase(it);
}

void RoomManager::leaveRoom(const LoggedUser& user)
{
	int roomId = getRoomIdByUser(user);
	auto it = m_rooms.find(roomId);
	if (it != m_rooms.end()) m_rooms.at(roomId).removeUser(user);
}

void RoomManager::joinRoom(const LoggedUser& user, unsigned int ID)
{
	auto it = m_rooms.find(ID);
	if (it == m_rooms.end()) throw std::exception("Invalid Room id!");
	if (it->second.getRoomState()) throw std::exception("Game already started!");
	if (it->second.getAllUsers().size() == it->second.getRoomData().maxPlayers) throw std::exception("The room is already full!");
	if (it->second.isUserInRoom(user)) throw std::exception("You can't be in multiple rooms simultaneously!");
	
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
	for (const auto& room : m_rooms)
		rooms.push_back(room.second.getRoomData());

	return rooms;
}

Room& RoomManager::getRoom(unsigned int ID)
{
	return m_rooms.at(ID);
}

unsigned int RoomManager::getRoomIdByUser(const LoggedUser& user) const
{
	if(m_rooms.size() == 0) throw std::exception("The user isn't in any room!");
	for (const auto& room : m_rooms)
	{
		if (room.second.isUserInRoom(user))
		{
			return room.second.getRoomData().id;
		}
	}

	throw std::exception("The user isn't in any room!");
}

unsigned int RoomManager::getIdCounter() const
{
	return m_idCounter;
}
