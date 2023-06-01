#pragma once
#include "LoggedUser.h"
#include "RoomData.h"
#include <vector>
#include <mutex>

class Room
{
public:
	Room(const LoggedUser& user, const RoomData& metadata) : m_metadata(metadata), m_admin(user) {};
	Room() = delete;
	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	const std::vector<LoggedUser>& getAllUsers() const;
	const unsigned int getRoomState() const;
	void startGame();
	RoomData getRoomData() const;
	bool isUserInRoom(const LoggedUser& user) const;
	LoggedUser getAdmin() const;
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
	std::mutex user_mutex;
	LoggedUser m_admin;
};

