#pragma once
#include <map>
#include "Room.h"

class RoomManager
{
public:
	void createRoom(const LoggedUser& user, const RoomData& roomData);
	void deleteRoom(unsigned int ID);
	unsigned int getRoomState(unsigned int ID) const;
	const std::map<unsigned int, Room>& getRooms() const;
	const Room& getRoom(unsigned int ID) const;
private:
	std::map<unsigned int, Room> m_rooms;
};

