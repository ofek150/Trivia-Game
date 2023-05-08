#pragma once
#include "LoggedUser.h"
#include "RoomData.h"
#include <vector>

class Room
{
public:
	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	std::vector<std::string> getAllUsers();
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

