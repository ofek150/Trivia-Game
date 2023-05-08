#pragma once
#include <map>
#include "Room.h"

class RoomManager
{
public:
	void createRoom(LoggedUser user, RoomData roomData);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	const std::vector<RoomData>& getRooms();
	Room& getRoom(int ID);
private:
	std::map<unsigned int, Room> m_rooms;
};

