#pragma once
#include <map>
#include <mutex>
#include "Room.h"
#include "SqliteDataBase.h"

class RoomManager
{
public:
	void operator=(const RoomManager&) = delete;

	// Public static function to get the singleton instance
	static RoomManager& getInstance()
	{
		static RoomManager instance;
		return instance;
	}

	void createRoom(const LoggedUser& user, const RoomData& roomData);
	void deleteRoom(unsigned int ID);
	void leaveRoom(const LoggedUser& user);
	void joinRoom(const LoggedUser& user, unsigned int ID);
	unsigned int getRoomState(unsigned int ID) const;
	std::map<unsigned int, Room>* getRooms();
	const std::vector<RoomData> getRoomsDatas() const;
	Room& getRoom(unsigned int ID);
	unsigned int getRoomIdByUser(const LoggedUser& user) const;
	unsigned int getIdCounter() const;

private:
	std::map<unsigned int, Room> m_rooms;
	std::mutex rooms_mutex;
	unsigned int m_idCounter = 0;

	// Private constructor to prevent instantiation from outside
	RoomManager()
	{
	}

	// Private copy constructor to prevent cloning
	RoomManager(const RoomManager&);
};
