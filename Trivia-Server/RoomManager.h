#pragma once
#include <map>
#include "Room.h"

class RoomManager
{
public:
	void operator=(const RoomManager&) = delete;

	// Public static function to get the singleton instance
	static RoomManager& getInstance() {
		static RoomManager instance;
		return instance;
	}

	void createRoom(const LoggedUser& user, const RoomData& roomData);
	void deleteRoom(unsigned int ID);
	void JoinRoom(const LoggedUser& user, unsigned int ID);
	unsigned int getRoomState(unsigned int ID) const;
	std::map<unsigned int, Room>* getRooms();
	const std::vector<RoomData> getRoomsDatas() const;
	const Room& getRoom(unsigned int ID) const;
private:
	std::map<unsigned int, Room> m_rooms;


	// Private constructor to prevent instantiation from outside
	RoomManager() {}

	// Private copy constructor to prevent cloning
	RoomManager(const RoomManager&);
};

