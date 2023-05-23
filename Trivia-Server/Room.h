#pragma once
#include "LoggedUser.h"
#include "RoomData.h"
#include <vector>

class Room
{
public:
	Room(const LoggedUser& user, const RoomData& metadata) : m_metadata(metadata), admin(user) {};
	Room() = delete;
	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	const std::vector<LoggedUser>& getAllUsers() const;
	const unsigned int getRoomState() const;
	RoomData getRoomData() const;
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
	LoggedUser admin;
};

