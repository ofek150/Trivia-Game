#include "Room.h"

void Room::addUser(const LoggedUser& user)
{
	m_users.push_back(user);
}

void Room::removeUser(const LoggedUser& user)
{
    auto it = std::find_if(m_users.begin(), m_users.end(),
        [&](const LoggedUser& u) { return u.getUsername() == user.getUsername(); });

    if (it != m_users.end())
    {
        if(user.getUsername() == admin.getUsername()) // Notify players to leave the server
        m_users.erase(it);
    }
}

const std::vector<LoggedUser>& Room::getAllUsers() const
{
    return m_users;
}

const unsigned int Room::getRoomState() const
{
    return m_metadata.isActive;
}

RoomData Room::getRoomData() const
{
    return m_metadata;
}
