#pragma once
#include "LoggedUser.h"
#include "RoomData.h"
#include <vector>

class Room
{
public:
	Room(const RoomData& metadata);
	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	const std::vector<LoggedUser>& getAllUsers() const;
	const unsigned int getRoomState() const;
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

